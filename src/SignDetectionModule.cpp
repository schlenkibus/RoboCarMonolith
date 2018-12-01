#include "SignDetectionModule.h"
#include "net/Client.h"

SignDetectionModule::Object SignDetectionModule::getPrediction() {
  auto response = Client::performRequest("localhost:8081");
  try {
    auto i = std::stoi(response);
    switch(i) {
      case 0:
        return Object::None;
      case 1:
        return Object::Stop;
      case 2:
        return Object::Block;
      default:
        return Object::None;
    }
  } catch(...) {
    return Object::None;
  }
}
