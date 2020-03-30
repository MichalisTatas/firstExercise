
add a .h and .c for data structures i.e. hash tables, trees, etc
# firstExercise

done : 

- created hash table
- created avl tree
- sorted list of patients
- finished q

to do :

- BETTER HASH FUNCTION THANK YOU MIKE
- checks for duplicates dates etc...
- finish binary max heap
- start question fullfiling prerequisits



UNDERSTANDING :: 

- diseaseHashTable : 

	has disease name for key
	
	for each separate disease in this ht we have a pointer to an avl tree which stores
	every patient with the same disease


- countryHashTable :

	has country name for key

	for each separate country every node holds a pointer to an avl tree which stores
	every patient taken health care in this country

** EVERY TREE HAS FOR KEY THE PATIENT'S ENTRYDATE**

sto existInTree an einai 0??
episis stin eisagwgh an exoun idia hmeromhnia eisagwghs edn ton bazw kan sto dentro?
afou den mpainoun oloi sto dentro prepei na paw psaksw thn lista mexri na brw diaforetikh hmeromhnia


gia ta 1a 2 queries

1st one 
	traverse the disease hash table and check if between the dates

2nd one
	if given disease use hash function
	else treverse the disease hash table
		check if between dates + in country if given
ELEGXOS AN IPRXEI MONO ! DATE KAI OCI 2

1ST QUERY DONE : 
	 i should add searching the list for patients with same dates!!

2ND QUERY DONE :
	country goes to the end or inbetween? 
