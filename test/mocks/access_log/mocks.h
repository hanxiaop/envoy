#pragma once

#include <memory>
#include <string>

#include "envoy/access_log/access_log.h"

#include "gmock/gmock.h"

namespace Envoy {
namespace AccessLog {

class MockAccessLogFile : public AccessLogFile {
public:
  MockAccessLogFile();
  ~MockAccessLogFile() override;

  // AccessLog::AccessLogFile
  MOCK_METHOD(void, write, (absl::string_view data));
  MOCK_METHOD(void, reopen, ());
  MOCK_METHOD(void, flush, ());
};

class MockFilter : public Filter {
public:
  MockFilter();
  ~MockFilter() override;

  // AccessLog::Filter
  MOCK_METHOD(bool, evaluate,
              (const Formatter::HttpFormatterContext&, const StreamInfo::StreamInfo&), (const));
};

class MockAccessLogManager : public AccessLogManager {
public:
  MockAccessLogManager();
  ~MockAccessLogManager() override;

  // AccessLog::AccessLogManager
  MOCK_METHOD(void, reopen, ());
  MOCK_METHOD(AccessLogFileSharedPtr, createAccessLog,
              (const Envoy::Filesystem::FilePathAndType& file_info));

  std::shared_ptr<MockAccessLogFile> file_{new testing::NiceMock<MockAccessLogFile>()};
};

class MockInstance : public Instance {
public:
  MockInstance();
  ~MockInstance() override;

  // AccessLog::Instance
  MOCK_METHOD(void, log,
              (const Http::RequestHeaderMap* request_headers,
               const Http::ResponseHeaderMap* response_headers,
               const Http::ResponseTrailerMap* response_trailers,
               const StreamInfo::StreamInfo& stream_info, AccessLogType access_log_type));
};

} // namespace AccessLog
} // namespace Envoy
