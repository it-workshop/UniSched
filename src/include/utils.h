#include <iostream>

#include <abstractui.h>
#include <abstractstorage.h>
#include <module.h>


namespace utils {

bool
select_modules (Core::AbstractUI **ui, Core::AbstractStorage **storage,
               std::vector<std::wstring>& args);

void init_iconv();
void deinit_iconv();

char * iconv(wchar_t *string);
const char * iconv(const wchar_t *string);
wchar_t * iconv(char *string);
const wchar_t * iconv(const char *string);
char * iconv(std::wstring& string);
const char * iconv(const std::wstring& string);
wchar_t * iconv(std::string& string);
const wchar_t * iconv(const std::string& string);

} // namespace utils end

