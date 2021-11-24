#include <Speaker.hpp>
#include <Callback.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

#include <sys/stat.h>

namespace Base {
namespace HttpClient {

Client::Client()
{
  mCurl.reset(curl_easy_init(), curl_easy_cleanup);
  if(mCurl.get() == nullptr)
    throw std::runtime_error("INVALID_CURL");
}

Interfaces::IHttpClient::HttpResponse Client::post(Interfaces::IHttpClient::HttpRequest req)
{
  return request("POST", req);
}

Interfaces::IHttpClient::HttpResponse Client::put(Interfaces::IHttpClient::HttpRequest req)
{
  return request("PUT", req);
}

Interfaces::IHttpClient::HttpResponse Client::get(Interfaces::IHttpClient::HttpRequest req)
{
  return request("GET", req);
}

Interfaces::IHttpClient::HttpResponse HttpClient::Client::request(const std::string& method, Interfaces::IHttpClient::HttpRequest req)
{
  std::string       url;
  size_t            responseCode;
  char*             contentType;
  std::stringstream writeStream;
  std::stringstream readStream;

  readStream << req.body;
  curl_slist* headers = nullptr;
  for (const auto& header : req.headers)
     headers = curl_slist_append(headers, std::string(header.first + ": " + header.second).c_str());

  url = req.url;
  bool isFirst = true;
  for(auto arg : req.uriArgs)
  {
    if(isFirst)
    {
      url    +='?';
      isFirst = false;
    }
    else
      url += '&';
    url += arg.first + '=' + arg.second;
  }
  if(req.headers.count("Content-type")>0)
  {
    if(req.headers.at("Content-type")=="image/jpg")
    {
//      FILE *fd = fopen(req.body.c_str(), "rb");
//      if(!fd)
//        throw::std::runtime_error("file doesn't exist");
//      struct stat file_info;
//      fstat(fileno(fd), &file_info);
      struct curl_httppost* Post = NULL;
      struct curl_httppost* last = NULL;
      curl_formadd(&Post, &last, CURLFORM_COPYNAME, "photo", CURLFORM_FILE, req.body.c_str(), CURLFORM_CONTENTTYPE, "image/jpeg", CURLFORM_END);

      (curl_easy_setopt)(mCurl.get(), CURLOPT_HTTPPOST, Post);
      (curl_easy_setopt)(mCurl.get(), CURLOPT_URL,           url.c_str());
      (curl_easy_setopt)(mCurl.get(), CURLOPT_CUSTOMREQUEST, method.c_str());
      (curl_easy_setopt)(mCurl.get(), CURLOPT_HTTPHEADER,    headers);
      (curl_easy_setopt)(mCurl.get(), CURLOPT_WRITEDATA,     &writeStream);
      (curl_easy_setopt)(mCurl.get(), CURLOPT_WRITEFUNCTION, Callback::write);
      //(curl_easy_setopt)(mCurl.get(), CURLOPT_POST,          1L);

      CURLcode code = curl_easy_perform(mCurl.get());
      if(code != CURLE_OK)
        throw std::runtime_error(curl_easy_strerror(code));

      (curl_easy_getinfo)(mCurl.get(), CURLINFO_RESPONSE_CODE, &responseCode);
      (curl_easy_getinfo)(mCurl.get(), CURLINFO_CONTENT_TYPE,  &contentType);
      curl_slist_free_all(headers);
      return { responseCode, contentType, writeStream.str() };
    }
  }
  (curl_easy_setopt)(mCurl.get(), CURLOPT_URL,           url.c_str());
  (curl_easy_setopt)(mCurl.get(), CURLOPT_CUSTOMREQUEST, method.c_str());
  (curl_easy_setopt)(mCurl.get(), CURLOPT_HTTPHEADER,    headers);
  (curl_easy_setopt)(mCurl.get(), CURLOPT_WRITEDATA,     &writeStream);
  (curl_easy_setopt)(mCurl.get(), CURLOPT_WRITEFUNCTION, Callback::write);
  (curl_easy_setopt)(mCurl.get(), CURLOPT_READFUNCTION,  Callback::read);
  (curl_easy_setopt)(mCurl.get(), CURLOPT_READDATA,      &readStream);
  (curl_easy_setopt)(mCurl.get(), CURLOPT_POST,          1L);
  (curl_easy_setopt)(mCurl.get(), CURLOPT_POSTFIELDS,    req.body.c_str());

  CURLcode code = curl_easy_perform(mCurl.get());
  if(code != CURLE_OK)
    throw std::runtime_error(curl_easy_strerror(code));

  (curl_easy_getinfo)(mCurl.get(), CURLINFO_RESPONSE_CODE, &responseCode);
  (curl_easy_getinfo)(mCurl.get(), CURLINFO_CONTENT_TYPE,  &contentType);
  curl_slist_free_all(headers);
  return { responseCode, contentType, writeStream.str() };
}

} // namespace HttpClient
} // namespace Base
