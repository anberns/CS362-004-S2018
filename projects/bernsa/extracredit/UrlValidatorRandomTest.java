/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Aaron Berns
 * UrlValidator Random Test Generator
 */

import junit.framework.TestCase;


public class UrlValidatorTest extends TestCase {

  

   public void testIsValid() {
	  
	   UrlValidator urlValidator = new UrlValidator();
	   
	   // test several thousand semi-random strings and print valid ones
	   for (int i = 0; i < 20000; i++){
		 
		   
		   double minChar = 33.;
		   double maxChar = 126.;	   
		   
		   // concatenate each possible section of url, starting with empty string
		   String randomUrl = "";
		   
		   // help with random number generation from dzone.com
		   char [] schemeChars = {'h', 'f', 't', 'p', ':', 's', '/'};
		   int j = 0;
		   randomUrl += schemeChars[((int)((Math.random()*((1-0)+1))+0))]; // 'h' or 'f'
		   randomUrl += 't';
		   randomUrl += schemeChars[((int)((Math.random()*((3-2)+1))+2))]; // 't' or 'p'
		   randomUrl += schemeChars[((int)((Math.random()*((4-3)+1))+3))]; // 'p', or ':'
		   
		   // make "://" more likely to follow valid schemes
		   if (randomUrl.charAt(3) == ':') {
			   randomUrl += '/';
			   randomUrl += '/';
			   
		   } else {
			   randomUrl += schemeChars[((int)((Math.random()*((6-4)+1))+4))]; // 's', ':' or '/'
			   if (randomUrl.charAt(4) == ':') {
				   randomUrl += '/';
				   randomUrl += '/';
				   
			   } else if (randomUrl.charAt(4) == 's') {
				   randomUrl += ':';
				   randomUrl += '/';
				   randomUrl += '/';
				   
			   } else {
				   randomUrl += schemeChars[((int)((Math.random()*((6-4)+1))+4))]; // 's', ':' or '/'
				   
			   }
		   }
		   
		   // fill in rest of url
		   
		   // 1/5 of urls have 'www'
		   int domainChoice = (int)((Math.random()*((5-0)+1))+0);
		   if (domainChoice == 1) {
			   randomUrl += "www.";
		   }
		   
		   // randomized domain of up to 100 characters
		   int randomDomainLength = (int)((Math.random()*((100-0)+1))+0);
		   for (j = 0; j < randomDomainLength; j++) {
				   randomUrl += (char)((int)((Math.random()*((maxChar-minChar)+1))+minChar));   
		   }
		   
		   // semi-randomized TLD
		   int domainChoice2 = (int)((Math.random()*((8-0)+1))+0);
		   if (domainChoice2 == 1) {
			   randomUrl += ".com";
		   }
		   else if (domainChoice2 == 2) {
			   randomUrl += ".edu";
		   }
		   else if (domainChoice2 == 3) {
			   randomUrl += ".org";
		   }
		   else if (domainChoice2 == 4) {
			   randomUrl += ".gov";
		   }
		   else if (domainChoice2 == 5) {
			   randomUrl += "";
		   }
		   else {
			   randomUrl += ".";
			   randomDomainLength = (int)((Math.random()*((4-0)+1))+0);
			   for (j = 0; j < randomDomainLength; j++) {
				   randomUrl += (char)((int)((Math.random()*((maxChar-minChar)+1))+minChar));   
			   }
		   }
		   
		   // possible randomized first path section
		   int pathChoice = (int)((Math.random()*((1-0)+1))+0);
		   if (pathChoice == 1) {
			   randomUrl += "/";
			   int randomPathLength = (int)((Math.random()*((50-0)+1))+0);
			   for (j = 0; j < randomPathLength; j++) {
				   randomUrl += (char)((int)((Math.random()*((maxChar-minChar)+1))+minChar));   
			   }
		   }
		   
		   // possible second path section
		   pathChoice = (int)((Math.random()*((1-0)+1))+0);
		   if (pathChoice == 1) {
			   randomUrl += "/";
			   int randomPathLength = (int)((Math.random()*((50-0)+1))+0);
			   for (j = 0; j < randomPathLength; j++) {
				   randomUrl += (char)((int)((Math.random()*((maxChar-minChar)+1))+minChar));   
			   }
		   }
		   
		   // randomized query string 
		   int queryChoice = (int)((Math.random()*((1-0)+1))+0);
		   if (queryChoice == 1) {
			   randomUrl += "/?";
			   int randomQueryLength = (int)((Math.random()*((10-0)+1))+0);
			   for (j = 0; j < randomQueryLength; j++) {
				   randomUrl += (char)((int)((Math.random()*((maxChar-minChar)+1))+minChar));   
			   }
			   
		   }
		   
		   // random chance of containing matching value
		   queryChoice = (int)((Math.random()*((1-0)+1))+0);
		   if (queryChoice == 1) {
			   randomUrl += "=";
			   int randomQueryLength = (int)((Math.random()*((10-0)+1))+0);
			   for (j = 0; j < randomQueryLength; j++) {
				   randomUrl += (char)((int)((Math.random()*((maxChar-minChar)+1))+minChar));   
			   }
			   
		   }
		   
		   // print valid urls
		   if (urlValidator.isValid(randomUrl)) {
			   System.out.println(randomUrl + " is valid");
		   }
		   
		   // remove comments to print invalid strings
		   // warning: there will be a lot
		   /*
		   else {
			   System.out.println(randomUrl + " is invalid");
		   
		   }
		   */
	   }
   }

}
