#include <Callback.hpp>

namespace Base {
namespace HttpClient {

size_t Callback::write(char* buffer, size_t block, size_t nmemb, std::ostream* stream)
{
  if (!buffer || !stream)
    throw std::runtime_error("INVALID_CALLBACK");

  size_t size = block * nmemb;
  stream->write(buffer, static_cast<std::streamsize>(size));
  return size;
}

size_t Callback::read(char* data, size_t /*block*/, size_t /*nmemb*/, std::istream* stream)
{
  if (!data || !stream)
    throw std::runtime_error("INVALID_CALLBACK");

  stream->seekg(0, stream->end);
  std::streamsize size = stream->tellg();
  stream->seekg(0, stream->beg);

  stream->read(data, size);
  return static_cast<size_t>(size);
}

} // namespace HttpClient
} // namespace Base
