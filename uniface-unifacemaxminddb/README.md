

## UnifaceMaxMindDB ##

This interfaces with the libmaxminddb library to expose that information to a Uniface application.

Copied directly from https://github.com/maxmind/libmaxminddb :

The libmaxminddb library provides a C library for reading MaxMind DB files, including the GeoIP2 databases from MaxMind. This is a custom binary format designed to facilitate fast lookups of IP addresses while allowing for great flexibility in the type of data associated with an address.

The MaxMind DB format is an open format. The spec is available at http://maxmind.github.io/MaxMind-DB/. This spec is licensed under the Creative Commons Attribution-ShareAlike 3.0 Unported License.

See http://dev.maxmind.com/ for more details about MaxMind's GeoIP2 products.

## Dependencies ##

UnifaceMaxMindDB has been written and tested with:

 * Uniface 9.7.01
  
## Setup ##

This project can be downloaded and setup standalone and requires Visual Studio 2013 to build the DLL. It also requires that you download the libmaxminddb project from github (https://github.com/maxmind/libmaxminddb) and use it as a dependency in the solution. The DLL has been pre-compiled can be copied from the bin directory.

A sample database has been included in the bin folder as well. (GeoLite2-City.mmdb)

## Usage ##

	char buf[128] = "GeoLite2-City.mmdb";
	char ip[32] = "216.58.217.132"; // Google
	 
	char location[32768];
	memset(location, 0, sizeof(location));
	
	LookupIPAddress(buf, ip, location);

Output will be the following:

```xml
<root>
  <city>
    <geoname_id>          5375480</geoname_id>
    <names>
      <de>Mountain View</de>
      <en>Mountain View</en>
      <fr>Mountain View</fr>
      <ru>Маунтин-Вью</ru>
      <zh-CN>芒廷维尤</zh-CN>
    </names>
  </city>
  <continent>
    <code>NA</code>
    <geoname_id>          6255149</geoname_id>
    <names>
      <de>Nordamerika</de>
      <en>North America</en>
      <es>Norteamérica</es>
      <fr>Amérique du Nord</fr>
      <ja>北アメリカ</ja>
      <pt-BR>América do Norte</pt-BR>
      <ru>Северная Америка</ru>
      <zh-CN>北美洲</zh-CN>
    </names>
  </continent>
  <country>
    <geoname_id>          6252001</geoname_id>
    <iso_code>US</iso_code>
    <names>
      <de>USA</de>
      <en>United States</en>
      <es>Estados Unidos</es>
      <fr>États-Unis</fr>
      <ja>アメリカ合衆国</ja>
      <pt-BR>Estados Unidos</pt-BR>
      <ru>США</ru>
      <zh-CN>美国</zh-CN>
    </names>
  </country>
  <location>
    <latitude>          37.419200</latitude>
    <longitude>          -122.057400</longitude>
    <metro_code>807</metro_code>
    <time_zone>America/Los_Angeles</time_zone>
  </location>
  <postal>
    <code>94043</code>
  </postal>
  <registered_country>
    <geoname_id>          6252001</geoname_id>
    <iso_code>US</iso_code>
    <names>
      <de>USA</de>
      <en>United States</en>
      <es>Estados Unidos</es>
      <fr>États-Unis</fr>
      <ja>アメリカ合衆国</ja>
      <pt-BR>Estados Unidos</pt-BR>
      <ru>США</ru>
      <zh-CN>美国</zh-CN>
    </names>
  </registered_country>
  <subdivisions>
    <subdivisions_array>
      <geoname_id>            5332921</geoname_id>
      <iso_code>CA</iso_code>
      <names>
        <de>Kalifornien</de>
        <en>California</en>
        <es>California</es>
        <fr>Californie</fr>
        <ja>カリフォルニア州</ja>
        <pt-BR>Califórnia</pt-BR>
        <ru>Калифорния</ru>
        <zh-CN>加利福尼亚州</zh-CN>
      </names>
    </subdivisions_array>
  </subdivisions>
</root> 
```

## Contributing to the project ##


## Contributors ##
* Thomas S. Shore III
