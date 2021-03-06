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

/*
 * DataWriter.cpp
 *
 */

#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/publisher/DataWriterImpl.hpp>

namespace eprosima {

using namespace fastrtps;

namespace fastdds {
namespace dds {

DataWriter::DataWriter(
        DataWriterImpl* impl)
    : impl_(impl)
{
}

DataWriter::~DataWriter()
{
}

bool DataWriter::write(
        void* data)
{
    return impl_->write(data);
}

bool DataWriter::write(
        void* data,
        fastrtps::rtps::WriteParams& params)
{
    return impl_->write(data, params);
}

ReturnCode_t DataWriter::write(
        void* data,
        const fastrtps::rtps::InstanceHandle_t& handle)
{
    return impl_->write(data, handle);
}

ReturnCode_t DataWriter::dispose(
        void* data,
        const fastrtps::rtps::InstanceHandle_t& handle)
{
    return impl_->dispose(data, handle);
}

bool DataWriter::dispose(
        void* data)
{
    return impl_->dispose(data);
}

const fastrtps::rtps::GUID_t& DataWriter::guid()
{
    return impl_->guid();
}

fastrtps::rtps::InstanceHandle_t DataWriter::get_instance_handle() const
{
    return impl_->get_instance_handle();
}

bool DataWriter::set_attributes(
        const fastrtps::rtps::WriterAttributes& att)
{
    return impl_->set_attributes(att);
}

const fastrtps::rtps::WriterAttributes& DataWriter::get_attributes() const
{
    return impl_->get_attributes();
}

ReturnCode_t DataWriter::set_qos(
        const DataWriterQos& qos)
{
    return impl_->set_qos(qos);
}

const DataWriterQos& DataWriter::get_qos() const
{
    return impl_->get_qos();
}

ReturnCode_t DataWriter::get_qos(
        DataWriterQos& qos) const
{
    qos = impl_->get_qos();
    return ReturnCode_t::RETCODE_OK;
}

ReturnCode_t DataWriter::set_listener(
        DataWriterListener* listener)
{
    return impl_->set_listener(listener);
}

const DataWriterListener* DataWriter::get_listener() const
{
    return impl_->get_listener();
}

bool DataWriter::set_topic(
        const TopicAttributes& att)
{
    return impl_->set_topic(att);
}

const TopicAttributes& DataWriter::get_topic() const
{
    return impl_->get_topic();
}

const Publisher* DataWriter::get_publisher() const
{
    return impl_->get_publisher();
}

ReturnCode_t DataWriter::wait_for_acknowledgments(
        const Duration_t& max_wait)
{
    return impl_->wait_for_acknowledgments(max_wait);
}

ReturnCode_t DataWriter::get_offered_deadline_missed_status(
        OfferedDeadlineMissedStatus& status)
{
    return impl_->get_offered_deadline_missed_status(status);
}

ReturnCode_t DataWriter::get_liveliness_lost_status(
        LivelinessLostStatus& status)
{
    return impl_->get_liveliness_lost_status(status);
}

ReturnCode_t DataWriter::assert_liveliness()
{
    return impl_->assert_liveliness();
}

} // namespace dds
} // namespace fastdds
} // namespace eprosima
