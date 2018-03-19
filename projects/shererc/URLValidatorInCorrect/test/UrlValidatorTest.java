/*******************************************************************************
 * Names: Nicholas Masie (masien), Caleb Sherer (shererc), Derek Sun (sunde)
 * Due Date: 03/19/2018
 * Assignment: Final Project part B
 * File: UrlValidatorTest.java
 * Description: UrlValidator class that tests the functionality of the 
 *  UrlValidator class. This is accomplished in three stages. The first is to
 *  manually test the functions of the UrlValidator. The second stage is to 
 *  test by partitioning. And the final stage is to test programatically. 
 *******************************************************************************/

import junit.framework.TestCase;
import java.util.Random;


public class UrlValidatorTest extends TestCase {
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   Random rand = new Random();
   /**
    * This function prints out the results of the valid test with relavent information
    * about the test including the string being tested and the scheme type. 
    * This function is our self written assert function. Since we do not want the program to stop
    * each time we find a bug, we have informative print statements instead.
    * @param testResult: what the url actually returned
    * @param tstString: The Url/portion of the url in string form 
    * @param validString: what the string result should be
    * @param schemeType: if all schemes are allowed or not
    */
   
   public void printTestResults(boolean testResult, String tstString, boolean validString, String schemeType) {
	   if(testResult == validString) {
		   if(testResult == true) {
			   System.out.println("TestString: " + tstString + " is verifed to be valid with schemeType: " + schemeType);
		   }else {
			   System.out.println("TestString: " + tstString + " is verified to be invalid with schemeType: " + schemeType);
		   }
	   } else {
		   System.out.println("Test String: " + tstString + " returned " + String.valueOf(testResult) + " from UrlValidator when it should have returned " +  String.valueOf(validString) + " with schemetype: " + schemeType);
	   }
   }
   
   /**
    * This function tests all the urls that are passed in to see if they are valid/invalid
    * @param testStrings: array of Strings containing test urls
    */
   public void randomTestInputs(ResultPair[] Schemes, ResultPair[] Ports, ResultPair[] Authorities) {
	   boolean validInput;
	   boolean validUrl;
	   String testString = "";
	   ResultPair testScheme;
	   ResultPair testPort;
	   ResultPair testAuth;
	   int randIndex;
	   //Initilize a new instance of UrlValidator with and without all schemes
	   UrlValidator UV = new UrlValidator();
	   UrlValidator UV2 = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //run it 100,000 times to check for valid combinations
	   for(int i = 0; i < 100000; i++) {
		   //Build the string of the url to be tested by getting one of each resultpair array
		   randIndex = rand.nextInt(Schemes.length);
		   testScheme = Schemes[randIndex];
		   randIndex = rand.nextInt(Ports.length);
		   testPort = Ports[randIndex];
		   randIndex = rand.nextInt(Authorities.length);
		   testAuth = Authorities[randIndex];
		   //build the string from the random values
		   testString = testScheme.item + testAuth.item + testPort.item;
		   //If only one of the resultPairs is false, then the whole url should be false
		   //The only time it is true is when all of the pairs are true
		   if(testScheme.valid == false || testAuth.valid == false || testPort.valid == false) {
			   validInput = false;
		   } else {
			   validInput = true;
		   }
		   //Try catch to attempt to prevent some of the bugs from crashing the program
		   try {
		   validUrl = UV.isValid(testString);
		   printTestResults(validUrl, testString, validInput, "NOT ALL");
		   System.out.println();
		   } catch(Exception e) {
			   System.out.println("TestString " + testString + " Tried to crash the program");
			   continue;
		   }
		   try {
		   validUrl = UV2.isValid(testString);
		   printTestResults(validUrl, testString, validInput, "ALL");
		   System.out.println();
		   } catch(Exception e) {
			   System.out.println("TestString " + testString + " Tried to crash the program");
			   continue;
		   }
	   }
		   //testString = testScheme.item + testPort.item + testAuth.item;
	 }
   
   /**
    * 
    */
   public void testPath() {

   }
   
   /**
    * Manually tests the functionality of UrlValidator
    */
   public void testManualTest() {
	   UrlValidator UV = new UrlValidator();
	   UrlValidator UV2 = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   boolean isValid;
	   
	   /* Manually testing valid urls */
	   isValid = UV.isValid("http://www.google.com");
	   printTestResults(isValid, "http://www.google.com", true, "NOT ALL");
	   System.out.println();
	   isValid = UV2.isValid("http://www.google.com");
	   printTestResults(isValid, "http://www.google.com", true, "ALL");
	   System.out.println();
	   
	   /*Manually testing invalid urls */
	   isValid = UV.isValid("http://.aaa.ewfesd");
	   printTestResults(isValid, "http://.aaa.ewfesd", false, "NOT ALL");
	   System.out.println();
	   isValid = UV2.isValid("http://.aaa.ewfesd");
	   printTestResults(isValid, "http://.aaa.ewfesd", false, "ALL");
	   System.out.println();
	   
	   
	   
	   
   }
   
   /**
    * This function build multiple different url strings to be tested 
    * and see which ones should and shouldn't pass.
    */
   public void testYourFirstPartition() {
	   UrlValidator UV = new UrlValidator();
	   UrlValidator UV2 = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   boolean isValid;
	   
	   
	   /**********************************************************************
	    * NOTE: This is valid tests however, since there is a REGEX bug in the
	    * source code, if we run this code, it will throw an exception. This 
	    * stops execution of the program, since we want to test other things
	    * we have it commented out.
	    * ********************************************************************/
	   /* partition testing the isValidAuthority function with valid authority */
	   /*isValid = UV.isValidAuthority("www.google.com");
	   printTestResults(isValid, "www.google.com", true, "NOT ALL");
	   System.out.println();
	   isValid = UV2.isValidAuthority("www.google.com");
	   printTestResults(isValid, "www.google.com", true, "ALL");
	   System.out.println();
	   
	   /* partition testing the isValidAuthority function with not valid authority */
	   /*isValid = UV.isValidAuthority(".badTest");
	   printTestResults(isValid, ".badTest", false, "NOT ALL");
	   System.out.println();
	   isValid = UV2.isValidAuthority(".badTest");
	   printTestResults(isValid, ".badTest", false, "ALL");
	   System.out.println();*/
	   
	   /*partition testing the isValidPath function with valid fragments */
	   isValid = UV.isValidPath("/goodTest");
	   printTestResults(isValid, "/goodTest", true, "NOT ALL");
	   System.out.println();
	   isValid = UV2.isValidPath("/goodTest");
	   printTestResults(isValid, "/goodTest", true, "ALL");
	   System.out.println();
	   
	   /*partition testing the isValidPath function with non-valid fragments */
	   isValid = UV.isValidPath("/#/badTest");
	   printTestResults(isValid, "/#/badTest", false, "NOT ALL");
	   System.out.println();
	   isValid = UV2.isValidPath("/#/badTest");
	   printTestResults(isValid, "/#/badTest", false, "ALL");
	   System.out.println();
	  
	   /*partition testing the isValidQuery function with valid queries */
	   isValid = UV.isValidQuery("?name=goodTest");
	   printTestResults(isValid, "?name=goodTest", true, "NOT ALL");
	   System.out.println();
	   isValid = UV2.isValidQuery("?name=goodTest");
	   printTestResults(isValid, "?name=goodTest", true, "ALL");
	   System.out.println();
	   
	   /*partition testing the isValidQuery function with non-valid queries */
	   isValid = UV.isValidQuery("namebadTest");
	   printTestResults(isValid, "namebadTest", false, "NOT ALL");
	   System.out.println();
	   isValid = UV2.isValidQuery("namebadTest");
	   printTestResults(isValid, "namebadTest", false, "ALL");
	   System.out.println();
	   
	   /*partition testing the isValidScheme function with valid schemes */
	   isValid = UV.isValidScheme("http");
	   printTestResults(isValid, "http", true, "NOT ALL");
	   System.out.println();
	   isValid = UV2.isValidScheme("http");
	   printTestResults(isValid, "http", true, "ALL");
	   System.out.println();
	   
	   /*partition testing the isValidScheme function with invalid schemes */
	   isValid = UV.isValidScheme("urls");
	   printTestResults(isValid, "urls", false, "NOT ALL");
	   System.out.println();
	   isValid = UV2.isValidScheme("urls");
	   printTestResults(isValid, "urls", false, "ALL");
	   System.out.println();
	   
   }
   
   /**
    * Builds url parts and passes them into a random tester to programmatically test 
    * different ways of building the urls.
    */
   public void testIsValid()
   {

	   //Get a bunch of true and false Schemes
	   ResultPair[] Schemes = {new ResultPair("http://", true),
               new ResultPair("ftp://", true),
               new ResultPair("https://", true),
               new ResultPair("3ht:sdfswe//", false),
               new ResultPair("http:/", false),
               new ResultPair("http/", false),
               new ResultPair(":", false),
               new ResultPair("", true),
               new ResultPair("HTTP://", true),
               new ResultPair("HTTPS://", true),
               new ResultPair("FTP://", true)
       };
	 //Get a bunch of true and false Ports
	   ResultPair[] Ports = {new ResultPair(":80", true),
               new ResultPair(":999999", false),
               new ResultPair(":9845", true),
               new ResultPair("", true),
               new ResultPair(":-1234234", false),
               new ResultPair(":65636",false),
               new ResultPair(":aasdfew", false),
               new ResultPair(":///4715s", false)
	   };
	 //Get a bunch of true and false Authorities
	   ResultPair[] Authorities = {
			   new ResultPair("www.google.com", true),
               new ResultPair("red.com", true),
               new ResultPair("blue.au", true),
               new ResultPair("0.0.0.0", true),
               new ResultPair("255.255.255.255", true),
               new ResultPair("3966.2585.259.256", false),
               new ResultPair("255.com", true),
               new ResultPair("blahblah.alsdfkj.", false),
               new ResultPair("a.b.c.", false),
               new ResultPair("test.a", false),
               new ResultPair("this.that/all", false),
               new ResultPair("blue.green.hello", false),
               new ResultPair("asdfkj.", false),
               new ResultPair(".asdjkf", false),
               new ResultPair("ellothere", false),
               new ResultPair("", false)
	   };
	   //Now test all of the strings to see if they are valid
	   try {
		   //Run the programmatic testing of the urls through random testing
		   randomTestInputs(Schemes, Ports, Authorities);
	   }catch(IndexOutOfBoundsException e) {
		   System.err.println("Caught index out of bounds exception + " + e);
	   }
	  
	  
   }

}
