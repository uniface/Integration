# README #

This README would normally document whatever steps are necessary to get your application up and running.

### What is this repository for? ###

* This sample uses UHTTP to call the Random.org web service that generates random Numbers, strings and sequences.  RANDOM.ORG is a true random number service that generates randomness via atmospheric noise and this sample uses its Integer Generator, String Generator and Sequence Generator.
* V1.0
* See: https://www.random.org/clients/http/

### How do I get set up? ###
This project can be downloaded and setup as standalone project.

### Setup RESTRandom as a standalone project ###

These instructions allow you to create a new stand alone project on your local machine.

 * For these steps you'll need the Project Setup Tool. Follow the instructions here https://github.com/uniface/Development-Tooling/tree/master/uniface-project-setup-tool to setup this tool before continuing
 * Make sure that the USYS97 variable is set according to the Project Setup Tool instructions.
 * Clone the RESTRandom repository onto your local machine. For these steps we'll assume it's been cloned into C:\Projects\RESTRandom
 * Open a command prompt in the root of the project and type "projectsetup97" to invoke the Project Setup Tool
 * Work through the setup process checking the details picked up by the setup tool make sense. Ignore referencies to userid and password they are not used.
 * You must restart the Uniface Development Tomcat and Uniface Development URouter
 * The URL for the web component will be http://localhost:8080/<Your Project Name>/wrd/RANDOM
 * When complete you can execute the C/S Form using the link or startup the development environment.
  

### Who do I talk to? ###

* Deana Wight 