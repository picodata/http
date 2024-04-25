#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <tpleval.h>

void term(int type, const char *str, size_t len, void *data)
{
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    const char *str = (const char *)data;
    tpe_parse(str, size, term, NULL);
    return 0;
}