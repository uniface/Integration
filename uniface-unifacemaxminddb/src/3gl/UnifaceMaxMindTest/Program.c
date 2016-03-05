#include <windows.h>  


/* UCMS_VERSION_ID("@(#)Program.c 9701:1 readonly 15-sep-2015 15:01:00(#)@") */
//---------------------------------------------------------------------------
// UnifaceMaxMindTest
//
// This test harness provides interfaces to the ported libmaxminddb DLL it expects the first parameter to be the filename of the MaxMindDB database, 
// otherwise it will attempt to open 'GeoLite2-City.mmdb' from the current directory and optionally the second parameter an IP address, 
// otherwise it will use the IP address of Google. It outputs the Geolocation to XML.
//
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

int main(int argc, char *argv[], char *envp[]) 	
{
	typedef int(*GW)(char *buf, char *ip, char *location);

	HMODULE hModule = LoadLibrary(TEXT("UnifaceMaxMindDB.DLL"));
	GW LookupIPAddress = (GW)GetProcAddress(hModule, "LookupIPAddress");

	char buf[128] = "GeoLite2-City.mmdb";
	char ip[32] = "216.58.217.132"; // Google
	 
	if (argc == 2) {
		strcpy(buf, argv[1]);
		printf("<!-- Using database file '%s' -->\n", buf);
	}

	if (argc == 3) {
		strcpy(ip, argv[2]);
		printf("<!-- Using IP address '%s' -->\n", ip);
	}

	char location[32768];
	memset(location, 0, sizeof(location));
	
	LookupIPAddress(buf, ip, location);
	printf("<!-- File = '%s', IP address used was = '%s' -->\n%s", buf, ip, location);
	 
}