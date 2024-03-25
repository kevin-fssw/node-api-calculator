#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <napi.h>

class Calculator : public Napi::ObjectWrap<Calculator> {
 public:
  // Javascript 생성자 함수
  static Napi::FunctionReference* functionRef;
  // Javasciprt 클래스 생성 및 초기화
  static Napi::Function Init(Napi::Env env);
  // 팩토리 함수
  static Napi::Object From(Napi::Env env, Napi::Value arg);
  // 생성자
  Calculator(const Napi::CallbackInfo& info);

 private:
  Napi::Value GetValue(const Napi::CallbackInfo& info);
  Napi::Value Add(const Napi::CallbackInfo& info);
  Napi::Value Subtract(const Napi::CallbackInfo& info);
  Napi::Value Multiply(const Napi::CallbackInfo& info);
  Napi::Value Divide(const Napi::CallbackInfo& info);

  double value_;
};

#endif