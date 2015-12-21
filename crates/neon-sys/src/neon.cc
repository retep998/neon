#include <new>
#include <nan.h>
#include <stdint.h>
#include <stdio.h>
#include "neon.h"

extern "C" void NeonSys_Call_SetReturn(Nan::FunctionCallbackInfo<v8::Value> *info, v8::Local<v8::Value> value) {
  info->GetReturnValue().Set(value);
}

extern "C" void *NeonSys_Call_GetIsolate(Nan::FunctionCallbackInfo<v8::Value> *info) {
  return (void *)info->GetIsolate();
}

extern "C" bool NeonSys_Call_IsConstructCall(Nan::FunctionCallbackInfo<v8::Value> *info) {
  return info->IsConstructCall();
}

extern "C" void NeonSys_Call_This(Nan::FunctionCallbackInfo<v8::Value> *info, v8::Local<v8::Object> *out) {
  *out = info->This();
}

extern "C" void NeonSys_Call_Callee(Nan::FunctionCallbackInfo<v8::Value> *info, v8::Local<v8::Function> *out) {
  *out = info->Callee();
}

extern "C" void NeonSys_Call_Data(Nan::FunctionCallbackInfo<v8::Value> *info, v8::Local<v8::Value> *out) {
  *out = info->Data();
}

extern "C" int32_t NeonSys_Call_Length(Nan::FunctionCallbackInfo<v8::Value> *info) {
  return info->Length();
}

extern "C" void NeonSys_Call_Get(Nan::FunctionCallbackInfo<v8::Value> *info, int32_t i, v8::Local<v8::Value> *out) {
  *out = (*info)[i];
}

extern "C" void NeonSys_Escape(v8::Local<v8::Value> *out, Nan::EscapableHandleScope *scope, v8::Local<v8::Value> value) {
  *out = scope->Escape(value);
}

extern "C" void NeonSys_NewObject(v8::Local<v8::Object> *out) {
  *out = Nan::New<v8::Object>();
}

extern "C" bool NeonSys_Object_GetOwnPropertyNames(v8::Local<v8::Array> *out, v8::Local<v8::Object> obj) {
  Nan::MaybeLocal<v8::Array> maybe = Nan::GetOwnPropertyNames(obj);
  return maybe.ToLocal(out);
}

extern "C" void *NeonSys_Object_GetIsolate(v8::Local<v8::Object> obj) {
  return obj->GetIsolate();
}

extern "C" void NeonSys_NewUndefined(v8::Local<v8::Primitive> *out) {
  *out = Nan::Undefined();
}

extern "C" void NeonSys_NewNull(v8::Local<v8::Primitive> *out) {
  *out = Nan::Null();
}

extern "C" void NeonSys_NewBoolean(v8::Local<v8::Boolean> *out, bool b) {
  *out = b ? Nan::True() : Nan::False();
}

extern "C" void NeonSys_NewInteger(v8::Local<v8::Integer> *out, v8::Isolate *isolate, int32_t x) {
  *out = v8::Integer::New(isolate, x);
}

extern "C" bool NeonSys_NewString(v8::Local<v8::String> *out, v8::Isolate *isolate, const uint8_t *data, int32_t len) {
  Nan::MaybeLocal<v8::String> maybe = v8::String::NewFromOneByte(isolate, data, v8::NewStringType::kNormal, len);
  return maybe.ToLocal(out);
}

extern "C" void NeonSys_NewNumber(v8::Local<v8::Number> *out, v8::Isolate *isolate, double value) {
  *out = v8::Number::New(isolate, value);
}

extern "C" void NeonSys_NewArray(v8::Local<v8::Array> *out, v8::Isolate *isolate, uint32_t length) {
  *out = v8::Array::New(isolate, length);
}

extern "C" bool NeonSys_Object_Get_Index(v8::Local<v8::Value> *out, v8::Local<v8::Object> obj, uint32_t index) {
  Nan::MaybeLocal<v8::Value> maybe = Nan::Get(obj, index);
  return maybe.ToLocal(out);
}

extern "C" bool NeonSys_Object_Set_Index(bool *out, v8::Local<v8::Object> object, uint32_t index, v8::Local<v8::Value> val) {
  Nan::Maybe<bool> maybe = Nan::Set(object, index, val);
  return maybe.IsJust() && (*out = maybe.FromJust(), true);
}

extern "C" bool NeonSys_Object_Get_Bytes(v8::Local<v8::Value> *out, v8::Local<v8::Object> obj, const uint8_t *data, int32_t len) {
  Nan::HandleScope scope;
  Nan::MaybeLocal<v8::String> maybe_key = v8::String::NewFromOneByte(v8::Isolate::GetCurrent(), data, v8::NewStringType::kNormal, len);
  v8::Local<v8::String> key;
  if (!maybe_key.ToLocal(&key)) {
    return false;
  }
  Nan::MaybeLocal<v8::Value> maybe = Nan::Get(obj, key);
  return maybe.ToLocal(out);
}

extern "C" bool NeonSys_Object_Set_Bytes(bool *out, v8::Local<v8::Object> obj, const uint8_t *data, int32_t len, v8::Local<v8::Value> val) {
  // FIXME: abstract the key construction logic to avoid duplication with ^^
  Nan::HandleScope scope;
  Nan::MaybeLocal<v8::String> maybe_key = v8::String::NewFromOneByte(v8::Isolate::GetCurrent(), data, v8::NewStringType::kNormal, len);
  v8::Local<v8::String> key;
  if (!maybe_key.ToLocal(&key)) {
    return false;
  }
  Nan::Maybe<bool> maybe = Nan::Set(obj, key, val);
  return maybe.IsJust() && (*out = maybe.FromJust(), true);
}

extern "C" bool NeonSys_Object_Get(v8::Local<v8::Value> *out, v8::Local<v8::Object> obj, v8::Local<v8::Value> key) {
  Nan::MaybeLocal<v8::Value> maybe = Nan::Get(obj, key);
  return maybe.ToLocal(out);
}

extern "C" bool NeonSys_Object_Set(bool *out, v8::Local<v8::Object> obj, v8::Local<v8::Value> key, v8::Local<v8::Value> val) {
  Nan::Maybe<bool> maybe = Nan::Set(obj, key, val);
  if (maybe.IsJust()) {
    *out = maybe.FromJust();
    return true;
  }
  return false;
}

extern "C" uint32_t NeonSys_Array_Length(v8::Local<v8::Array> array) {
  return array->Length();
}

extern "C" int32_t NeonSys_String_Utf8Length(v8::Local<v8::String> str) {
  return str->Utf8Length();
}

extern "C" size_t NeonSys_String_Data(char *out, size_t len, v8::Local<v8::Value> str) {
  return Nan::DecodeWrite(out, len, str, Nan::UTF8);
}

extern "C" bool NeonSys_Value_ToString(v8::Local<v8::String> *out, v8::Local<v8::Value> value) {
  Nan::MaybeLocal<v8::String> maybe = Nan::To<v8::String>(value);
  return maybe.ToLocal(out);
}

extern "C" bool NeonSys_Value_ToObject(v8::Local<v8::Object> *out, v8::Local<v8::Value> *value) {
  Nan::MaybeLocal<v8::Object> maybe = Nan::To<v8::Object>(*value);
  return maybe.ToLocal(out);
}

extern "C" bool NeonSys_NewBuffer(v8::Local<v8::Object> *out, uint32_t size) {
  Nan::MaybeLocal<v8::Object> maybe = Nan::NewBuffer(size);
  return maybe.ToLocal(out);
}

extern "C" void NeonSys_Buffer_Data(buf_t *out, v8::Local<v8::Object> obj) {
  out->data = node::Buffer::Data(obj);
  out->len = node::Buffer::Length(obj);
}

extern "C" bool NeonSys_IsBuffer(v8::Local<v8::Value> obj) {
  return node::Buffer::HasInstance(obj);
}

extern "C" void NeonSys_Chained(void *out, void *closure, NeonSys_ChainedScopeCallback callback, void *parent_scope) {
  Nan::EscapableHandleScope v8_scope;
  callback(out, parent_scope, &v8_scope, closure);
}

extern "C" void NeonSys_Nested(void *out, void *closure, NeonSys_NestedScopeCallback callback, void *realm) {
  Nan::HandleScope v8_scope;
  callback(out, realm, closure);
}

extern "C" void NeonSys_ExecFunctionBody(void *closure, NeonSys_RootScopeCallback callback, Nan::FunctionCallbackInfo<v8::Value> *info, void *scope) {
  Nan::HandleScope v8_scope;
  callback(info, closure, scope);
}

extern "C" void NeonSys_ExecModuleBody(void *kernel, NeonSys_ModuleScopeCallback callback, v8::Local<v8::Object> exports, void *scope) {
  Nan::HandleScope v8_scope;
  callback(kernel, exports, scope);
}

class KernelWrapper : public Nan::ObjectWrap {
public:
  inline void *GetKernel() { return this->kernel; }
  static inline void SetKernel(v8::Local<v8::Object> obj, void *kernel) {
    KernelWrapper *wrapper = new KernelWrapper(kernel);
    wrapper->Wrap(obj);
  }
private:
  explicit KernelWrapper(void *kernel) : kernel(kernel) { }
  ~KernelWrapper() { }
  void *kernel;
};

extern "C" bool NeonSys_NewFunction(v8::Local<v8::Function> *out, v8::Isolate *isolate, Nan::FunctionCallback callback, void *kernel) {
  v8::Local<v8::ObjectTemplate> env_tmpl = v8::ObjectTemplate::New(isolate);
  env_tmpl->SetInternalFieldCount(1);
  v8::MaybeLocal<v8::Object> maybe_env = env_tmpl->NewInstance(isolate->GetCurrentContext());
  v8::Local<v8::Object> env;
  if (!maybe_env.ToLocal(&env)) {
    return false;
  }
  KernelWrapper::SetKernel(env, kernel);
  Nan::MaybeLocal<v8::Function> maybe_result = Nan::New<v8::Function>(callback, env);
  return maybe_result.ToLocal(out);
}

extern "C" void *NeonSys_FunctionKernel(v8::Local<v8::Object> obj) {
  return Nan::ObjectWrap::Unwrap<KernelWrapper>(obj)->GetKernel();
}

extern "C" tag_t NeonSys_TagOf(v8::Local<v8::Value> val) {
  return val->IsNull()                    ? tag_null
    : val->IsUndefined()                  ? tag_undefined
    : (val->IsTrue() || val->IsFalse())   ? tag_boolean
    : (val->IsInt32() || val->IsUint32()) ? tag_integer // FIXME: this isn't right for large int64s
    : val->IsNumber()                     ? tag_number
    : val->IsString()                     ? tag_string
    : val->IsArray()                      ? tag_array
    : val->IsFunction()                   ? tag_function
    : val->IsObject()                     ? tag_object
                                          : tag_other;
}

extern "C" bool NeonSys_IsUndefined(v8::Local<v8::Value> val) {
  return val->IsUndefined();
}

extern "C" bool NeonSys_IsNull(v8::Local<v8::Value> val) {
  return val->IsNull();
}

extern "C" bool NeonSys_IsInteger(v8::Local<v8::Value> val) {
  return val->IsInt32() || val->IsUint32();
}

extern "C" bool NeonSys_IsNumber(v8::Local<v8::Value> val) {
  return val->IsNumber();
}

extern "C" bool NeonSys_IsBoolean(v8::Local<v8::Value> val) {
  return val->IsBoolean();
}

extern "C" bool NeonSys_IsString(v8::Local<v8::Value> val) {
  return val->IsString();
}

extern "C" bool NeonSys_IsObject(v8::Local<v8::Value> val) {
  // FIXME: is the null check superfluous?
  return val->IsObject() && !val->IsNull();
}

extern "C" bool NeonSys_IsArray(v8::Local<v8::Value> val) {
  return val->IsArray();
}

extern "C" bool NeonSys_IsFunction(v8::Local<v8::Value> val) {
  return val->IsFunction();
}

extern "C" bool NeonSys_IsTypeError(v8::Local<v8::Value> val) {
  return false; // FIXME: implement this
}

extern "C" void NeonSys_ThrowAny(v8::Local<v8::Value> val) {
  Nan::ThrowError(val);
}

extern "C" bool NeonSys_NewTypeError(v8::Local<v8::Value> *out, const char *msg) {
  *out = Nan::TypeError(msg);
  return true;
}

extern "C" void NeonSys_ThrowTypeError(const char *msg) {
  Nan::ThrowTypeError(msg);
}

extern "C" bool NeonSys_SameHandle(v8::Local<v8::Value> v1, v8::Local<v8::Value> v2) {
  return v1 == v2;
}