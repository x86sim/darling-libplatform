/*
 * iOS simulator (iOS 26) compatibility exports.
 *
 * The simulator runtime's libsystem_c re-exports the string/memory routines
 * from the host libsystem_platform, as modern macOS does. Darling keeps them
 * as _platform_* only, so export the public names here.
 */

#include <stddef.h>
#include <stdint.h>

void* _platform_memmove(void* dst, const void* src, size_t n);
void* _platform_memset(void* b, int c, size_t len);
void* _platform_memchr(const void* s, int c, size_t n);
int _platform_memcmp(const void* s1, const void* s2, size_t n);
void* _platform_memccpy(void* dst, const void* src, int c, size_t n);
void _platform_bzero(void* s, size_t n);
void _platform_memset_pattern4(void* b, const void* pattern4, size_t len);
void _platform_memset_pattern8(void* b, const void* pattern8, size_t len);
void _platform_memset_pattern16(void* b, const void* pattern16, size_t len);
char* _platform_strchr(const char* s, int c);
int _platform_strcmp(const char* s1, const char* s2);
char* _platform_strcpy(char* dst, const char* src);
size_t _platform_strlcat(char* dst, const char* src, size_t size);
size_t _platform_strlcpy(char* dst, const char* src, size_t size);
size_t _platform_strlen(const char* s);
int _platform_strncmp(const char* s1, const char* s2, size_t n);
char* _platform_strncpy(char* dst, const char* src, size_t n);
char* _platform_strstr(const char* s1, const char* s2);

#define EXPORT __attribute__((visibility("default")))

EXPORT void* memcpy(void* dst, const void* src, size_t n) { return _platform_memmove(dst, src, n); }
EXPORT void* memmove(void* dst, const void* src, size_t n) { return _platform_memmove(dst, src, n); }
EXPORT void* memchr(const void* s, int c, size_t n) { return _platform_memchr(s, c, n); }
EXPORT int memcmp(const void* s1, const void* s2, size_t n) { return _platform_memcmp(s1, s2, n); }
EXPORT int bcmp(const void* s1, const void* s2, size_t n) { return _platform_memcmp(s1, s2, n); }
EXPORT void* memccpy(void* dst, const void* src, int c, size_t n) { return _platform_memccpy(dst, src, c, n); }
EXPORT void bzero(void* s, size_t n) { _platform_bzero(s, n); }
EXPORT void memset_pattern4(void* b, const void* p, size_t len) { _platform_memset_pattern4(b, p, len); }
EXPORT void memset_pattern8(void* b, const void* p, size_t len) { _platform_memset_pattern8(b, p, len); }
EXPORT void memset_pattern16(void* b, const void* p, size_t len) { _platform_memset_pattern16(b, p, len); }
EXPORT char* strchr(const char* s, int c) { return _platform_strchr(s, c); }
EXPORT char* index(const char* s, int c) { return _platform_strchr(s, c); }
EXPORT int strcmp(const char* s1, const char* s2) { return _platform_strcmp(s1, s2); }
EXPORT char* strcpy(char* dst, const char* src) { return _platform_strcpy(dst, src); }
EXPORT size_t strlcat(char* dst, const char* src, size_t size) { return _platform_strlcat(dst, src, size); }
EXPORT size_t strlcpy(char* dst, const char* src, size_t size) { return _platform_strlcpy(dst, src, size); }
EXPORT size_t strlen(const char* s) { return _platform_strlen(s); }
EXPORT int strncmp(const char* s1, const char* s2, size_t n) { return _platform_strncmp(s1, s2, n); }
EXPORT char* strncpy(char* dst, const char* src, size_t n) { return _platform_strncpy(dst, src, n); }
EXPORT char* strstr(const char* s1, const char* s2) { return _platform_strstr(s1, s2); }

// memset itself is defined in string/generic/bzero.c

// Returns nonzero if the 8-byte-aligned buffer contains any nonzero byte
EXPORT unsigned long _platform_memcmp_zero_aligned8(const void* s, size_t n)
{
	const uint64_t* p = (const uint64_t*) s;
	for (size_t i = 0; i < n / 8; i++)
		if (p[i])
			return 1;
	return 0;
}
