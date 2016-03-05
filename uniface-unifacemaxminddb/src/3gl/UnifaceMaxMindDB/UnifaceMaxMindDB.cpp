#include <stdio.h>
#include <tchar.h> 

#include <strsafe.h>
#include "umsw3gl.h"
#include <math.h> 
#include <string.h> 
#include <io.h>
#include <malloc.h>
#include <direct.h>
#include <stdlib.h> 
#include <process.h> 
#include <complex.h>
#include "maxminddb.h"  
#include "tap.h"


#define R_OK 4
#pragma comment(lib, "Ws2_32.lib")

// Enable Visual Style
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#pragma endregion

#ifdef __cplusplus
extern "C"
{
#endif


	/* UCMS_VERSION_ID("@(#)UnifaceMaxMindDB.cpp 9701:1 readonly 15-sep-2015 15:01:00(#)@") */
	//---------------------------------------------------------------------------
	// UnifaceMaxMindDB
	//
	// This DLL provides interfaces with the libmaxminddb library.
	// The libmaxminddb library provides a C library for reading MaxMind DB files, including the GeoIP2 databases from MaxMind. 
	// This is a custom binary format designed to facilitate fast lookups of IP addresses while allowing for great flexibility in the type of data associated with an address.
	// The MaxMind DB format is an open format.The spec is available at http ://maxmind.github.io/MaxMind-DB/. 
	// This spec is licensed under the Creative Commons Attribution-ShareAlike 3.0 Unported License.
	// See http ://dev.maxmind.com/ for more details about MaxMind's GeoIP2 products.
	// 
	// You have a royalty-free right to use, modify, reproduce and distribute
	// this sample code (and/or any modified version) in any way you find useful,
	// provided that you agree that Uniface has no warranty obligations or
	// liability for any sample code which has been modified.
	//
	//-seq--chg#----date----who--description---------------------------------------
	//   0  2		150915  tss  created
	//---------------------------------------------------------------------------



	XEXPORT(long) LookupIPAddress(char *path, char *ipaddress, char *iplocation);
	char mykeybase[1024], *mykey = NULL;


	MMDB_s *open_ok(const char *db_file, int mode, const char *mode_desc)
	{
		if (0 != _access(db_file, R_OK)) {
			BAIL_OUT(
				"could not read the specified file - %s\nIf you are in a git checkout try running 'git submodule update --init'",
				db_file);
		}

		MMDB_s *mmdb = (MMDB_s *)calloc(1, sizeof(MMDB_s));

		if (NULL == mmdb) {
			BAIL_OUT("could not allocate memory for our MMDB_s struct");
		}

		int status = MMDB_open(db_file, mode, mmdb);

		int is_ok = ok(MMDB_SUCCESS == status, "open %s status is success - %s",
			db_file, mode_desc);

		if (!is_ok) {
			diag("open status code = %d (%s)", status, MMDB_strerror(status));
			free(mmdb);
			return NULL;
		}

		is_ok = ok(NULL != mmdb, "returned mmdb struct is not null for %s - %s",
			db_file, mode_desc);

		if (!is_ok) {
			free(mmdb);
			return NULL;
		}

		return mmdb;
	}

	MMDB_lookup_result_s lookup_string_ok(MMDB_s *mmdb, const char *ip, const char *file, const char *mode_desc)
	{
		int gai_error, mmdb_error;
		MMDB_lookup_result_s result = MMDB_lookup_string(mmdb, ip, &gai_error, &mmdb_error);


		return result;
	}


#ifndef HAVE_OPEN_MEMSTREAM /* win32 version */

	static void addONode(int o_stream_number, FILE *file, char **buf, size_t *length);
	static void delONode(FILE *file);
	static int get_o_stream_number(void);
	static void setODirName(char *str);
	static void setOFileName(char *str, int stream_number);

	struct oListNode
	{
		int o_stream_number;
		FILE *file;
		char **buf;
		size_t *length;
		struct oListNode *pnext;
	};

	static struct oListNode *oList = NULL;

	static void addONode(
		int o_stream_number,
		FILE *file,
		char **buf,
		size_t *length)
	{
		struct oListNode **pcur = &oList;
		struct oListNode *node = (oListNode*)calloc(1, sizeof(struct oListNode));

		if (node == NULL)
			abort();

		while ((*pcur) && (*pcur)->o_stream_number < o_stream_number)
			pcur = &((*pcur)->pnext);

		node->pnext = *pcur;
		node->o_stream_number = o_stream_number;
		node->file = file;
		node->buf = buf;
		node->length = length;
		(*pcur) = node;
	}

	static void delONode(FILE *file)
	{
		struct oListNode **pcur = &oList;
		struct oListNode *todel;
		char file_name[30];

		while ((*pcur) && (*pcur)->file != file)
			pcur = &((*pcur)->pnext);

		todel = (*pcur);
		if (todel == NULL){ //not found
			// WARNING(("Trying to close a simple FILE* with close_memstream()"));
		}
		else {
			if (EOF == fflush(file))
				abort();
			if ((*(todel->length) = ftell(file)) == -1)
				abort();
			if ((*(todel->buf) = (char *)calloc(1, *(todel->length) + 1)) == NULL)
				abort();
			if (EOF == fseek(file, 0, SEEK_SET))
				abort();
			fread(*(todel->buf), 1, *(todel->length), file);

			fclose(file);
			setOFileName(file_name, todel->o_stream_number);
			if (-1 == remove(file_name))
				abort();

			(*pcur) = todel->pnext;
			free(todel);
		}
	}


	static int get_o_stream_number(void)
	{
		int o_stream_number = 1;
		struct oListNode *cur = oList;

		while (cur && o_stream_number >= cur->o_stream_number){
			o_stream_number++;
			cur = cur->pnext;
		}
		return o_stream_number;
	}

	static void setODirName(char *str)
	{
		sprintf(str, "ostr_job_%d", _getpid());
	}

	static void setOFileName(char *str, int stream_number)
	{
		setODirName(str);
		char fname[30];
		sprintf(fname, "/o_stream_%d", stream_number);
		strcat(str, fname);
	}

	FILE *open_memstream(char **ptr, size_t *sizeloc)
	{
		FILE *f;
		char file_name[30];
		int o_stream_number;

		if (oList == NULL){
			setODirName(file_name);
			_mkdir(file_name);
		}

		o_stream_number = get_o_stream_number();
		setOFileName(file_name, o_stream_number);
		f = fopen(file_name, "w+");

		if (!f)
			return NULL;

		addONode(o_stream_number, f, ptr, sizeloc);

		return f;
	}


	void close_memstream(FILE *f)
	{
		char file_name[30];
		delONode(f);

		if (oList == NULL){
			setODirName(file_name);
			_rmdir(file_name);
		}
	}

#else

	void	close_memstream(FILE *f)
	{
		fclose(f);
	}

#endif /* HAVE_OPEN_MEMSTREAM */



	/* *INDENT-OFF* */

	/* The memmem, strdup, and strndup functions were all copied from the
	* FreeBSD source, along with the relevant copyright notice.
	*
	* It'd be nicer to simply use the functions available on the system if they
	* exist, but there doesn't seem to be a good way to detect them without also
	* defining things like _GNU_SOURCE, which we want to avoid, because then we
	* end up _accidentally_ using GNU features without noticing, which then
	* breaks on systems like OSX.
	*
	* C is fun! */

	/* Applies to memmem implementation */
	/*-
	* Copyright (c) 2005 Pascal Gloor <pascal.gloor@spale.com>
	*
	* Redistribution and use in source and binary forms, with or without
	* modification, are permitted provided that the following conditions
	* are met:
	* 1. Redistributions of source code must retain the above copyright
	*    notice, this list of conditions and the following disclaimer.
	* 2. Redistributions in binary form must reproduce the above copyright
	*    notice, this list of conditions and the following disclaimer in the
	*    documentation and/or other materials provided with the distribution.
	* 3. The name of the author may not be used to endorse or promote
	*    products derived from this software without specific prior written
	*    permission.
	*
	* THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
	* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	* ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
	* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
	* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	* SUCH DAMAGE.
	*/
	static void *		mmdb_memmem(const void *l, size_t l_len, const void *s, size_t s_len)
	{
		register char *cur, *last;
		const char *cl = (const char *)l;
		const char *cs = (const char *)s;

		/* we need something to compare */
		if (l_len == 0 || s_len == 0)
			return NULL;

		/* "s" must be smaller or equal to "l" */
		if (l_len < s_len)
			return NULL;

		/* special case where s_len == 1 */
		if (s_len == 1)
			return (void *)memchr(l, (int)*cs, l_len);

		/* the last position where its possible to find "s" in "l" */
		last = (char *)cl + l_len - s_len;

		for (cur = (char *)cl; cur <= last; cur++)
			if (cur[0] == cs[0] && memcmp(cur, cs, s_len) == 0)
				return cur;

		return NULL;
	}

	/* Applies to strnlen implementation */
	/*-
	* Copyright (c) 2009 David Schultz <das@FreeBSD.org>
	* All rights reserved.
	*
	* Redistribution and use in source and binary forms, with or without
	* modification, are permitted provided that the following conditions
	* are met:
	* 1. Redistributions of source code must retain the above copyright
	*    notice, this list of conditions and the following disclaimer.
	* 2. Redistributions in binary form must reproduce the above copyright
	*    notice, this list of conditions and the following disclaimer in the
	*    documentation and/or other materials provided with the distribution.
	*
	* THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
	* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	* ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
	* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
	* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	* SUCH DAMAGE.
	*/
	static size_t
		mmdb_strnlen(const char *s, size_t maxlen)
	{
		size_t len;

		for (len = 0; len < maxlen; len++, s++) {
			if (!*s)
				break;
		}
		return (len);
	}

	/* Applies to strdup and strndup implementation */
	/*
	* Copyright (c) 1988, 1993
	*	The Regents of the University of California.  All rights reserved.
	*
	* Redistribution and use in source and binary forms, with or without
	* modification, are permitted provided that the following conditions
	* are met:
	* 1. Redistributions of source code must retain the above copyright
	*    notice, this list of conditions and the following disclaimer.
	* 2. Redistributions in binary form must reproduce the above copyright
	*    notice, this list of conditions and the following disclaimer in the
	*    documentation and/or other materials provided with the distribution.
	* 3. Neither the name of the University nor the names of its contributors
	*    may be used to endorse or promote products derived from this software
	*    without specific prior written permission.
	*
	* THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
	* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	* ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
	* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
	* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	* SUCH DAMAGE.
	*/
	static char *		mmdb_strdup(const char *str)
	{
		size_t len;
		char *copy;

		len = strlen(str) + 1;
		if ((copy = (char *)malloc(len)) == NULL)
			return (NULL);
		memcpy(copy, str, len);
		return (copy);
	}

	static char *		mmdb_strndup(const char *str, size_t n)
	{
		size_t len;
		char *copy;

		len = mmdb_strnlen(str, n);
		if ((copy = (char *)malloc(len + 1)) == NULL)
			return (NULL);
		memcpy(copy, str, len);
		copy[len] = '\0';
		return (copy);
	}
	/* *INDENT-ON* */



	void print_indentation(FILE *stream, int i)
	{
		char buffer[1024];
		int size = i >= 1024 ? 1023 : i;
		memset(buffer, 32, size);
		buffer[size] = '\0';
		fputs(buffer, stream);
	}

	char *bytes_to_hex(uint8_t *bytes, uint32_t size)
	{
		char *hex_string = (char *)malloc((size * 2) + 1);
		char *hex_pointer = hex_string;

		for (uint32_t i = 0; i < size; i++) {
			sprintf(hex_pointer + (2 * i), "%02X", bytes[i]);
		}

		return hex_string;
	}


#define _PFX_64  "ll"
#define PRIX64       _PFX_64 "X"
#define PRIu64       _PFX_64 "u"

	MMDB_entry_data_list_s *dump_entry_data_list(FILE *stream, MMDB_entry_data_list_s *entry_data_list, int indent, int *status)
	{
		//char lastkey[1024];
		char *key;

		switch (entry_data_list->entry_data.type) {
		case MMDB_DATA_TYPE_MAP:
		{
			uint32_t size = entry_data_list->entry_data.data_size;

			print_indentation(stream, indent);

			indent += 2;

			for (entry_data_list = entry_data_list->next; size && entry_data_list; size--) {

				key = mmdb_strndup((char *)entry_data_list->entry_data.utf8_string, entry_data_list->entry_data.data_size);

				if (NULL == key) {
					*status = MMDB_OUT_OF_MEMORY_ERROR;
					return NULL;
				}

				mykey = strdup(key);

				print_indentation(stream, indent);
				fprintf(stream, "<%s>", key);

				entry_data_list = entry_data_list->next;
				entry_data_list = dump_entry_data_list(stream, entry_data_list, indent + 2, status);


				if (MMDB_SUCCESS != *status) {
					return NULL;
				}
				fprintf(stream, "</%s>", key);
			}

			indent -= 2;
			print_indentation(stream, indent);
			//	fprintf(stream, "</%s>\n", key);
			free(key);

		}
		break;
		case MMDB_DATA_TYPE_ARRAY:
		{
			uint32_t size = entry_data_list->entry_data.data_size;
			char *holdkey = mykey;
			print_indentation(stream, indent);
			fprintf(stream, "<%s_array>\n", holdkey);
			indent += 2;

			for (entry_data_list = entry_data_list->next; size && entry_data_list; size--) {
				entry_data_list = dump_entry_data_list(stream, entry_data_list, indent, status);
				if (MMDB_SUCCESS != *status) {
					return NULL;
				}
			}

			indent -= 2;
			print_indentation(stream, indent);
			fprintf(stream, "</%s_array>\n", holdkey);
			free(holdkey);
		}
		break;
		case MMDB_DATA_TYPE_UTF8_STRING:
		{
			char *string = mmdb_strndup((char *)entry_data_list->entry_data.utf8_string, entry_data_list->entry_data.data_size);
			if (NULL == string) {
				*status = MMDB_OUT_OF_MEMORY_ERROR;
				return NULL;
			}
			//print_indentation(stream, indent);
			fprintf(stream, "%s", string);
			free(string);
			entry_data_list = entry_data_list->next;
		}
		break;
		case MMDB_DATA_TYPE_BYTES:
		{
			char *hex_string = bytes_to_hex((uint8_t *)entry_data_list->entry_data.bytes, entry_data_list->entry_data.data_size);
			if (NULL == hex_string) {
				*status = MMDB_OUT_OF_MEMORY_ERROR;
				return NULL;
			}

			print_indentation(stream, indent);
			fprintf(stream, "%s", hex_string);

			free(hex_string);

			entry_data_list = entry_data_list->next;
		}
		break;
		case MMDB_DATA_TYPE_DOUBLE:
			print_indentation(stream, indent);
			fprintf(stream, "%f", entry_data_list->entry_data.double_value);
			entry_data_list = entry_data_list->next;
			break;
		case MMDB_DATA_TYPE_FLOAT:
			print_indentation(stream, indent);
			fprintf(stream, "%f", entry_data_list->entry_data.float_value);
			entry_data_list = entry_data_list->next;
			break;
		case MMDB_DATA_TYPE_UINT16:
			print_indentation(stream, indent);
			fprintf(stream, "%u", entry_data_list->entry_data.uint16);
			entry_data_list = entry_data_list->next;
			break;
		case MMDB_DATA_TYPE_UINT32:
			print_indentation(stream, indent);
			fprintf(stream, "%u", entry_data_list->entry_data.uint32);

			entry_data_list = entry_data_list->next;
			break;
		case MMDB_DATA_TYPE_BOOLEAN:
			print_indentation(stream, indent);
			fprintf(stream, "%s", entry_data_list->entry_data.boolean ? "true" : "false");

			entry_data_list = entry_data_list->next;
			break;
		case MMDB_DATA_TYPE_UINT64:
			print_indentation(stream, indent);
			fprintf(stream, "%" PRIu64 " ", entry_data_list->entry_data.uint64);

			entry_data_list = entry_data_list->next;
			break;
		case MMDB_DATA_TYPE_UINT128:
			print_indentation(stream, indent);
			//#if MMDB_UINT128_IS_BYTE_ARRAY
			char *hex_string;
			hex_string = bytes_to_hex((uint8_t *)entry_data_list->entry_data.uint128, 16);
			//char *hex_string = bytes_to_hex((uint8_t *)entry_data_list->entry_data.uint128, 16);
			fprintf(stream, "0x%s ", hex_string);

			free(hex_string);
			//#else
			//			uint64_t high = entry_data_list->entry_data.uint128 >> 64;
			//			uint64_t low = (uint64_t)entry_data_list->entry_data.uint128;
			//			fprintf(stream, "0x%016" PRIX64 "%016" PRIX64 " <uint128>\n", high,
			//				low);
			//#endif
			entry_data_list = entry_data_list->next;
			break;
		case MMDB_DATA_TYPE_INT32:
			print_indentation(stream, indent);
			fprintf(stream, "%d ", entry_data_list->entry_data.int32);

			entry_data_list = entry_data_list->next;
			break;
		default:
			*status = MMDB_INVALID_DATA_ERROR;
			return NULL;
		}


		*status = MMDB_SUCCESS;
		return entry_data_list;
	}


	XEXPORT(long) LookupIPAddress(char *path, char *ip, char *iplocation) {

		char outputBufferStr[32768], *outputBuffer = NULL;

		size_t size;
		FILE *stream;
		int exit_code = 0;

		size = sizeof(outputBuffer);

		MMDB_s mmdb;
		int status = MMDB_open(path, MMDB_MODE_MMAP, &mmdb);

		if (MMDB_SUCCESS != status) {
			sprintf(outputBuffer, "\n  Can't open %s - %s\n", path, MMDB_strerror(status));

			if (MMDB_IO_ERROR == status) {
				sprintf(outputBuffer, "    IO error: %s\n", strerror(errno));
			}
			exit_code = -1;

			sprintf(iplocation, "%s", outputBuffer);
			goto end;
		}

		int gai_error, mmdb_error;


		MMDB_lookup_result_s result = MMDB_lookup_string(&mmdb, ip, &gai_error, &mmdb_error);

		MMDB_entry_data_list_s *entry_data_list = NULL;


		if (result.found_entry) {
			int status = MMDB_get_entry_data_list(&result.entry, &entry_data_list);

			if (MMDB_SUCCESS != status) {
				sprintf(outputBuffer, "Got an error looking up the entry data - %s\n", MMDB_strerror(status));
				sprintf(iplocation, "%s", outputBuffer);
				exit_code = -4;
				goto end;
			}

			if (NULL != entry_data_list) {
				stream = open_memstream(&outputBuffer, &size);
				int status;
				dump_entry_data_list(stream, entry_data_list, 2, &status);
				close_memstream(stream);
				sprintf(iplocation, "<root>%s</root>", outputBuffer);
			}
		}
		else {
			sprintf(outputBuffer, "\n  No entry for this IP address (%s) was found\n\n", ip);
			sprintf(iplocation, "%s", outputBuffer);
			exit_code = -5;
		}

	end:
		MMDB_free_entry_data_list(entry_data_list);
		MMDB_close(&mmdb);


		return exit_code;
	}


#ifdef __cplusplus
}
#endif
