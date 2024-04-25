#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <httpfast.h>

int handle_param(void *uobj, const char *name, size_t name_len, const char *value, size_t value_len)
{
    // Simple check to allow branch visiting when calling param callback
    if (name_len % 2 == 0)
    {
        return 0;
    }

    return 1;
}

void on_error(void *uobj, int code, const char *fmt, va_list ap)
{
}

void on_warn(void *uobj, int code, const char *fmt, va_list ap)
{
}

int on_header(void *uobj,
              const char *name, size_t name_len,
              const char *value, size_t value_len,
              int is_continuation)
{
    return 0;
}

int on_body(void *uobj, const char *body, size_t body_len)
{
    return 0;
}

int on_request_line(void *uobj,
                    const char *method, size_t method_len,
                    const char *path, size_t path_len,
                    const char *query, size_t query_len,
                    int http_major, int http_minor)
{
    return 0;
}

int on_response_line(void *uobj,
                     unsigned code,
                     const char *reason, size_t reason_len,
                     int http_major, int http_minor)
{
    return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    const char *str = (const char *)data;

    struct parse_http_events event_callbacks_one = {
        .on_error = on_error,
        .on_warn = on_warn,
        .on_header = on_header,
        .on_body = on_body,
        .on_request_line = NULL,
        .on_response_line = on_response_line};
    struct parse_http_events event_callbacks_two = {
        .on_error = on_error,
        .on_warn = on_warn,
        .on_header = on_header,
        .on_body = on_body,
        .on_request_line = on_request_line,
        .on_response_line = NULL};
    httpfast_parse(str, size, &event_callbacks_one, NULL);
    httpfast_parse(str, size, &event_callbacks_two, NULL);
    httpfast_parse_params(str, size, handle_param, NULL);
    return 0;
}
