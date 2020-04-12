#include <napi.h>
using namespace Napi;
String Hello(const CallbackInfo& info) {
  return String::New(info.Env(), "world");
}
void Init(Env env, Object exports, Object module) {
  exports.Set("hello", Function::New(env, Hello));
}
NODE_API_MODULE(addon, Init)

