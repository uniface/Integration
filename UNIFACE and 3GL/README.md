# Metaphone #

This demonstrates the construction and integration of C on a Windows platform with Uniface 9.7. For this example we will call a DLL that has an implementation of the Metaphone phonetic algorithm for indexing words by their English pronunciation. (See http://en.wikipedia.org/wiki/Metaphone)

## Dependencies ##

Metaphone has been written and tested with:

 * Uniface 9.7.01
 * SQLite
  
## Setup ##

This project can be downloaded and setup standalone.


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