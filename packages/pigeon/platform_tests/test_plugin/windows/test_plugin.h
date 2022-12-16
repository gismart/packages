// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_PLUGIN_TEST_PLUGIN_H_
#define FLUTTER_PLUGIN_TEST_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>
#include <optional>
#include <string>

#include "pigeon/core_tests.gen.h"

namespace test_plugin {

// This plugin handles the native side of the integration tests in
// example/integration_test/
class TestPlugin : public flutter::Plugin,
                   public core_tests_pigeontest::HostIntegrationCoreApi {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows* registrar);

  TestPlugin(flutter::BinaryMessenger* binary_messenger);

  virtual ~TestPlugin();

  // Disallow copy and assign.
  TestPlugin(const TestPlugin&) = delete;
  TestPlugin& operator=(const TestPlugin&) = delete;

  // HostIntegrationCoreApi.
  std::optional<core_tests_pigeontest::FlutterError> Noop() override;
  core_tests_pigeontest::ErrorOr<core_tests_pigeontest::AllTypes> EchoAllTypes(
      const core_tests_pigeontest::AllTypes& everything) override;
  std::optional<core_tests_pigeontest::FlutterError> ThrowError() override;
  core_tests_pigeontest::ErrorOr<std::optional<std::string>>
  ExtractNestedString(
      const core_tests_pigeontest::AllTypesWrapper& wrapper) override;
  core_tests_pigeontest::ErrorOr<core_tests_pigeontest::AllTypesWrapper>
  CreateNestedString(const std::string& string) override;
  core_tests_pigeontest::ErrorOr<core_tests_pigeontest::AllTypes>
  SendMultipleTypes(bool a_bool, int64_t an_int,
                    const std::string& a_string) override;
  core_tests_pigeontest::ErrorOr<int64_t> EchoInt(int64_t an_int) override;
  core_tests_pigeontest::ErrorOr<double> EchoDouble(double a_double) override;
  core_tests_pigeontest::ErrorOr<bool> EchoBool(bool a_bool) override;
  core_tests_pigeontest::ErrorOr<std::string> EchoString(
      const std::string& a_string) override;
  core_tests_pigeontest::ErrorOr<std::vector<uint8_t>> EchoUint8List(
      const std::vector<uint8_t>& a_uint8_list) override;
  void NoopAsync(std::function<
                 void(std::optional<core_tests_pigeontest::FlutterError> reply)>
                     result) override;
  void EchoAsyncString(
      const std::string& a_string,
      std::function<void(core_tests_pigeontest::ErrorOr<std::string> reply)>
          result) override;
  void CallFlutterNoop(
      std::function<
          void(std::optional<core_tests_pigeontest::FlutterError> reply)>
          result) override;
  void CallFlutterEchoString(
      const std::string& a_string,
      std::function<void(core_tests_pigeontest::ErrorOr<std::string> reply)>
          result) override;

 private:
  std::unique_ptr<core_tests_pigeontest::FlutterIntegrationCoreApi>
      flutter_api_;
};

}  // namespace test_plugin

#endif  // FLUTTER_PLUGIN_TEST_PLUGIN_H_