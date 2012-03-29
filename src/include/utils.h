#include <iostream>

#include <abstractui.h>
#include <abstractstorage.h>
#include <module.h>


namespace utils {

bool
select_modules (Core::AbstractUI **ui, Core::AbstractStorage **storage,
               std::vector<std::string>& args);

void init_iconv();
void deinit_iconv();

char * to_char(wchar_t *string);
const char * to_char(const wchar_t *string);

wchar_t * to_wchar(char *string);
const wchar_t * to_wchar(const char *string);

} // namespace utils end

