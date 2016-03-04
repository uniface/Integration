# uniwinhook #

This utility dll has been created to fulfill two functions not available in the Uniface product set. With it you can achieve two features namely:
Replacement drag-n-drop form title bar.
IPC copydata communication between Uniface apps on the same machine/desktop

## Dependencies ##

This build has been created using Visual Studio 2013 12.0.31101.00 Update 4. 
The dll functions on Windows 8.1 and is usable with Uniface 
versions 9.6.05, 9.6.06 and v9.7.01

 * SQLite
 
 There is a dependency to include the 3GL Uniface libraries which is set within the project definition.
 Currently the project points to the current solutions directory $(SolutionsDir)\3gl\ as the base folder for
 * includes
 * lib
 subfolders
 The contents of which are compatiple with Uniface 9.6.05 - 9.7.01
 You will need to adjust within the project definition for compilation and linking to your local version and folder(s) for Uniface.

## Setup ##

This project can be downloaded and setup standalone.

### Setup uniwinhook as a standalone project ###
These instructions allow you to create a new stand alone project on your local machine.

 * After cloning open visual studio solution file uniWinHook.sln
 * adjust project definitions for compilation and linking to point to your Uniface include and lib foders on your local machine.
 * Adjsut as appropriate for debug or release versions
 * Rebuild solution.
 
### Deploying ###
To deploy owithin a project either copy the dll to the uniface install common/bin folder or alternatively add the location of the dll to the {USER_3GL] section within your assignment file. 
 
## Contributing to the project ##

To set up the project for development follow the steps above to create uOutlook as a standalone project. Once complete the only other tool required is the Version Control project, allowing granular exports of source code suitable for use with BitBucket. To set this up follow these steps:

 * Visit https://bitbucket.org/uniface/version-control and follow the setup instructions to download the Version Control tool
 * Open the IDE and using the Utilities->Import menu import the file FILESYNC_Menu.xml. Assuming you extracted the Version Control tool to C:\\UnifacePackages, this would be found in C:\\UnifacePackages\\VersionControl\\imports
 * Compile the additional menu, which will in turn compile the menu we just imported
 * In the IDE go to Utilities->Preferences->General and tick the check box "Enable Additional Menu"
 * Now that the additional menu is enabled we can go to Utilities->Additional->Settings and using the browse button next to "Uniface Source Directory" select ./src. This points the tool at our source code.
 * Everything is now setup and we can go to Utilities->Additional->Project to verify that everything is setup correctly. Visiting this screen will sync your Uniface repository with the src folder. If it's working correctly then you should see the contents of this folder in the tree view.

## Contributors ##

* George Mockford

## Acknowledgements ##
* Daniel Iseli  UniWinHook  dll