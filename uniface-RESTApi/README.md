# REST Api #

This demonstrates the construction and integration of a REST Api in Uniface.

## Dependencies ##

Metaphone has been written and tested with:

 * Uniface 9.7.01
 * SQLite
  
## Setup ##

This project can be downloaded and setup standalone. Import the RESTApi.XML export and compile everything.
This has not been setup to use the project import wizard as of yet.


## Using ##

Point a browser to http://localhost:8080/uniface/wrd/REPAPI/xref/APICUSTOMER
You may need to adjust the port (8080) to reflect your environment.

## Contributing to the project ##

To set up the project for development follow the steps above to create Metaphone as a standalone project. Once complete the only other tool required is the Version Control project, allowing granular exports of source code suitable for use with BitBucket. To set this up follow these steps:

 * Visit https://bitbucket.org/uniface/version-control and follow the setup instructions to download the Version Control tool
 * Open the IDE and using the Utilities->Import menu import the file FILESYNC_Menu.xml. Assuming you extracted the Version Control tool to C:\\UnifacePackages, this would be found in C:\\UnifacePackages\\VersionControl\\imports
 * Compile the additional menu, which will in turn compile the menu we just imported
 * In the IDE go to Utilities->Preferences->General and tick the check box "Enable Additional Menu"
 * Now that the additional menu is enabled we can go to Utilities->Additional->Settings and using the browse button next to "Uniface Source Directory" select ./src. This points the tool at our source code.
 * Everything is now setup and we can go to Utilities->Additional->Project to verify that everything is setup correctly. Visiting this screen will sync your Uniface repository with the src folder. If it's working correctly then you should see the contents of this folder in the tree view.

## Contributors ##
* Thomas S. Shore III