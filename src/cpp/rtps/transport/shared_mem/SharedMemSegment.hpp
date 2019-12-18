// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _FASTDDS_SHAREDMEM_SEGMENT_H_
#define _FASTDDS_SHAREDMEM_SEGMENT_H_

#include <boostconfig.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/thread/thread_time.hpp>

#include "SharedMemUUID.hpp"

namespace eprosima {
namespace fastdds {
namespace rtps {

/**
 * Provides shared memory functionallity abstrating from
 * lower level layers
 */
class SharedMemSegment
{
public:

    typedef std::ptrdiff_t offset;
    typedef boost::interprocess::interprocess_condition condition_variable;
    typedef boost::interprocess::interprocess_mutex mutex;
    typedef boost::interprocess::named_mutex named_mutex;

    static constexpr boost::interprocess::open_only_t open_only = boost::interprocess::open_only_t();
    static constexpr boost::interprocess::create_only_t create_only = boost::interprocess::create_only_t();
    static constexpr boost::interprocess::open_or_create_t open_or_create = boost::interprocess::open_or_create_t();

    // Boost memory manager needs extra memory to maintain its structures,
    // as these structures are shared they are stored in the segment.
    // TODO: Further analysis to determine the perfect value for this extra segment size
    static constexpr uint32_t EXTRA_SEGMENT_SIZE = 512;

    SharedMemSegment(
            boost::interprocess::create_only_t,
            const std::string& name,
            size_t size)
        : segment_(boost::interprocess::create_only, name.c_str(), size + EXTRA_SEGMENT_SIZE)
        , name_(name)
    {

    }

    SharedMemSegment(
            boost::interprocess::open_only_t,
            const std::string& name)
        : segment_(boost::interprocess::open_only, name.c_str())
        , name_(name)
    {
    }

    SharedMemSegment(
            boost::interprocess::open_or_create_t,
            const std::string& name,
            size_t size)
        : segment_(boost::interprocess::create_only, name.c_str(), size)
        , name_(name)
    {
    }

    void* get_address_from_offset(
            SharedMemSegment::offset offset) const
    {
        return segment_.get_address_from_handle(offset);
    }

    SharedMemSegment::offset get_offset_from_address(
            void* address) const
    {
        return segment_.get_handle_from_address(address);
    }

    boost::interprocess::managed_shared_memory& get() { return segment_;}

    static void remove(
            const std::string& name)
    {
        boost::interprocess::shared_memory_object::remove(name.c_str());
    }

    std::string name()
    {
        return name_;
    }

    /**
     * Estimates the extra segment' space required for an allocation
     */
    static uint32_t compute_per_allocation_extra_size(size_t allocation_alignment)
    {
        try
        {
            Id uuid;
            boost::interprocess::managed_shared_memory 
                    test_segment(boost::interprocess::create_only, uuid.to_string().c_str(), (std::max)((size_t)1024,allocation_alignment*4));

            auto m1 = test_segment.get_free_memory();
            test_segment.allocate_aligned(1, allocation_alignment);
            auto m2 = test_segment.get_free_memory();
            return static_cast<uint32_t>(m1-m2);

        }
        catch(const std::exception&)
        {
            return 48; // This has been meaured in Ubuntu 64-bit app
        }
    }

    class Id
    {
    public:

        typedef UUID type;

        Id()
        {
        }

		Id(const Id& other)
		{
			uuid_ = other.uuid_;
		}

        const type& get() const
        {
            return uuid_;
        }

        std::string to_string()
        {
            return uuid_.to_string();
        }

    private:

        UUID uuid_;

    }; // Id

private:

    boost::interprocess::managed_shared_memory segment_;

    std::string name_;
};

} // namespace rtps
} // namespace fastdds
} // namespace eprosima

#endif // _FASTDDS_SHAREDMEM_SEGMENT_H_
