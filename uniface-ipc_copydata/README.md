# IPC_CopyData #

IPC_CopyData is an example of inter process communication using the windows standard copydata feature.  Although the standard technique for inter process communication is via urouter messaging this mechanism can be complex and relies on an install of Uniface urouter which can be a little too much for a simple local install of Uniface. This example provides for simple messaging between Uniface instances on the same machine providing the means for asyncronous processes for long transactiona for eaxample complex search patterns.
Provided in the demo are two uniface applications, one acting as a hidden application message server and process request processing component, and the other as a basic search by name and display. The table to be searched is a 1 million row table of United Kingdom addresses and person details. Each is unique and the basic task is to search for matching names. The search program messages the message server that returns a limited number of keys to the calling process for retrieval and display. While the search is in progress the search screen can continue to be actioned by the end user. When the list of qualifying people keys are returned the screen is refreshed.
Although simple in it's implementation hopefully it provides the mechanism to build a more comprehensive asyncronous task engine for a wide variety of actions.
The message "server" is initiated automatically by the search screen on startup and is shutdown when the search process ends. Naturally this can be modified to suit.
Provided on the search screen are several buttons that cause the server to become 'unhidden' and/or rehidden and report status. Realistically only for demonstrations to verify/prove the server state and existence.

## Dependencies ##

IPC_CopyData has been written and tested with:

 * Uniface 9.7.01
 * SQLite
  
 ## Setup ##

This project can be downloaded and setup standalone.

### Setup IPC_CopyData as a standalone project ###
These instructions allow you to create a new stand alone project on your local machine.

 * For these steps you'll need the Project Setup Tool. Follow the instructions here https://bitbucket.org/uniface/project-setup-tool to setup this tool before continuing
 * Clone the IPC_CopyData repository onto your local machine. For these steps we'll assume it's been cloned into C:\Projects\IPC_CopyData
 * Open a command prompt in the root of the project and type "projectsetup97" to invoke the Project Setup Tool
 * Work through the setup process checking the details picked up by the setup tool make sense. Ignore referencies to userid and password they are not used.
 * When complete click on one of the presentation links
 ## dependency ##
 
 This example relies on the uniwinhook dll contained within the 'ext' folder.
  
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