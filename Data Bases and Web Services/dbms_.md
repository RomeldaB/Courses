#  :heart: Data Bases and Web Services
  
#  Database design :butterfly:
  
* Conceptual <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> construct description of info disregarding tech.
* Logical <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> construct descr based on specific data model w/o implementation.
* Physical <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> perform implementation using particular dbms.
  
####  Conceptual :spider:
  
* Entity <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> real world obj distinguishable from others.
* Entity set<img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> collection of similar entities (Employees). They have attributes, and keys.
* Relationship <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> association among 2+ entities.
* Relationship set <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/>  collection of similar relationships.
* Constraints 
    :moon: Multiplicity <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> how many entities can participate in a rel.
    :moon: Participation <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> Ent set is total if all entities participate in the rel. Partial if some don't.
* Weak entity <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> Identified uniquely only by considering primary key of the owner entity
    :hole: Owner - weak ent must be in 1:n rel
    :hole: Weak ent must have total participation in the rel
* ISA hierarchy <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/>  same as inheritance
* Aggregation <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> considering a relationship as an entity OR relationship involving a relationship set.
* (Ndoshta s'eshte) **UML** <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> Class model at the core of OO dev and design. An instance is like an entity and the class as the set.
  
#  Relational Model (Logical) :bug:
  
* Relation:
    :rose:  schema (Specifies name of relation plus name and type of each column)
    :rose: instance (a table with rows(#-> cardinality), and columns(# -> degree)) 
    - A row is called tuple, column is an attribute.
* Insert a tuple 
``` sql
INSERT INTO Students (sid, name, login, gpa)
VALUES (123, 'Tani', 'tani@jac-uni.de', 1.2)
```
* Delete tuples 
``` sql
DELETE FROM Students S
WHERE S.name = 'Mut'
```
* Update tuples 
``` sql
UPDATE Students S
SET gpa = 3
WHERE S.name = 'Mut'
```
* Integrity constraints <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> condition that must be true for any instance of the database. Specified when shema defined and are checked when relations are modified.
  
* Primary key <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> no 2 diff tuples have same value of this field. This may not be true for any subset of the key. If part 2 false <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> **superkey**
  
* Foreign key <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> A field (set of fields) that is used to refer to a tuple in another relation. It must correspond to the prim key of the second relation
  
* Create table with references
``` sql
CREATE TABLE WORKS_IN
(
    ssn CHAR(11),
    did INTEGER UNIQUE,
    since DATE NOT NULL,
    PRIMARY KEY (ssn, did),
    FOREIGN KEY (ssn)
        REFERENCES Employees
        ON DELETE CASCADE
        ON UPDATE SET DEFAULT
    FOREIGN KEY (did)
        REFERENCES Deps
)
```
  
* Referential integrity <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> Default is NO ACTION, other values include CASCADE, SET NULL or SET DEFAULT.
  
* When translating ISA to tables (3 ways)
    :cake: Separate tables(relation) for each ent set
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/>    * Must use delete cascade
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/>    * Queries involving all employees easy
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/>    * Those involving just a specific one require join to get some attributes
    :cake: 2 relations (only the specific ones)
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/>    * Each emplyee(for ex) must be in one of the 2
    :cake: One big table (Overlap? Covering?)
  
* View is like a relation but we also store definition rather that a set of tuples
```sql
CREATE VIEW YoungStds(name, grade)
AS SELECT S.name, E.grade
    FROM Students S, Enrolled E
    WHERE S.sid = E.sid AND S.age < 21
```
* DROP TABLE can be used. Also DROP VIEW
* Views can be useful for personalized information while hiding details in underlying relations.
  
#  Relational Algebra :rabbit:
  
* Selection <img src="https://latex.codecogs.com/gif.latex?&#x5C;sigma_{gpa&lt;4}"/>  <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> select based on a condition
* Projection <img src="https://latex.codecogs.com/gif.latex?&#x5C;pi_{name,login}"/>  <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> select only specified attributes in the specified order
* Cartesian product <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> We know this
* Natural join <img src="https://latex.codecogs.com/gif.latex?R_1%20&#x5C;bowtie_{bid}%20R_2"/>  <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> Equate attrubutes of same name. Project out redundant attr
* Query <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> {S | S <img src="https://latex.codecogs.com/gif.latex?&#x5C;in"/> Sailors logical_and S.rating > 8}
  
#  Query processing :snake:
  
* The order is <img src="https://latex.codecogs.com/gif.latex?&#x5C;longrightarrow"/> From, where, group by, having, select, order by.
```sql
SELECT *
FROM Bla
WHERE Bla.m = 7
GROUP BY Bla.rating
HAVING Count(*) > 1
ORDER BY Bla.rating
```
* Query is parsed into a relational algebra expr 
    :cucumber: SELECT as <img src="https://latex.codecogs.com/gif.latex?&#x5C;pi"/>
    :cucumber: FROM as X
    :cucumber: WHERE as <img src="https://latex.codecogs.com/gif.latex?&#x5C;bowtie"/> OR <img src="https://latex.codecogs.com/gif.latex?&#x5C;sigma"/> depending if it references one or 2 tables.
    :cucumber: Views are expanded and flattened
* Logical Plan created (Logical query tree)
* Logical plan is optimized (heuristic optimization) and turned to physical
    :tomato: Logical tree into more efficient logical tree
    :tomato: ex. push all predicates down
* Physical plan optimized(cost-based optimization) then execution
    :carrot: Ideally find best plan, practically avoid worst plans
* Summary 
    * Query tree <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> internal representation of query
        :lemon: Logical tree based on relational algebra
        :lemon: Physical tree based on concrete algorithms
    * Optimization <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> modify tree to perform
        :lemon: Logical opt <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> query rewriting
        :lemon: Physical opt <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> black magic
#  Database app dev :sheep:
  
* Create special API(application prog interface) to call sql commands Or embed sql
  
```c
<html>
<head>
    <title> Nje titull kot </title>
</head>
<body>
    <?php $mysql = mysql_connect( “localhost”, “apache”, “DBWAisCool” );
    $result = mysql_db_query( “books”, “SELECT isbn, author, title FROM book_info" )
        or die( “query failed “);
    ?>
    <table>
        <tr> <th>ISBN</th> <th>Author(s)</th> <th>Title</th> </tr>
  
        <?php while ( $array = mysql_fetch_array($result) ); ?>
        <tr>
            <td><?php echo $array[ "isbn" ]; ?></td>
            <td><?php echo $array[ "author" ]; ?></td>
            <td><?php echo $array[ "title" ]; ?></td>
        </tr>    
        <?php endwhile; ?>
    </table>
    <?php mysql_close($mysql); ?>
</body>
</html>
```
  
#  Web services :elephant:
  
* Each comp has world wide unique id:
    :avocado: IP address (32 bit IPv4 and 128 in IPv6)
    :avocado: Domain name: subdomain.host.top-level-domain
    :avocado: Domain Name Server to resolve
* Uniform Resource Identifiers (http://www.dabadaba.com/index.html)
    :pineapple: Naming scheme (http)
    :pineapple: Name of host comp + optional port nr (.com:80)
    :pineapple: Name of resource (index.html)
    :pineapple: Uniform Resource Locater subset of it
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :lemon: Used for identification via location
* HTTP 
    * Is a commun protocol (set of rules defining the structure of msg and comm process)
    * When clicking a link on the web
        :orange: Client connects to server, transmits http request
        :orange: Server generates and transmits response
        :orange: Both disconnect
* HTTP request structure
    * Request line (GET  ~/index.html HTTP/1.1)
        :pear: http method field 
        :pear: local resource
        :pear: http version
    * type of client
    * type of file
* HTTP response struct
    * Status line (HTTP/1.1 200 OK)
        :watermelon: Http version
        :watermelon: status code
        :watermelon: status msg
    * Date when obj was created
    * Nr of bytes sent
    * type of sent obj
    * payload (kodi)
* SGML a type of markup language that introduced tags but is complex and not used
* HTML hyper text markup lang
    * Based in SGML
    * Css
``` c
<link rel="stylesheet" type = "text/css" href="books.css">
```
* Document Object Model <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> platform and language neutral interface that allows programs and scripts to dynammically access and update content and structure of HTML docs
  
#  3-Tier Architecture :fish:
  
1. Presentation
    :cloud: The user interface
    :cloud: Needs to adapt to screen size
1. Application logic
    :cloud: Implement bussines logic
    :cloud: Access to dbms
1. Data management
    :cloud: \>=1 dbms
* Clients
    * Thin <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Client implements 1 and Server 2,3
    * Thick <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Client implements 1,2 and server 3
        :sunny: Do not scale
* Single tier arch
    * Server does all
    * Adv <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> easy to maintain
    * Des <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> User expects UI
* In 3 tier arch 
    * 1 is done by Client program (html css js)
    * 2 application server
    * 3 by a dbms (tables, xml, json)
* ADVANTAGES
    * Scalibility
    * Thin clients
    * Software dev
        :moon: Code for business logic is centralized
    * Heterogeneous systems
        :moon: Tiers can be independently maintained
    * Integrated data access
        :moon: Several db-s can be handeled in the middle tier
* The application tier
    :snowflake: Encodes business logic 
    :snowflake: Connects to database
    :snowflake: Accepts form input from first tier
    :snowflake: Generates output of the presentation tier
* Where to keep app state? 
    :star: Client-side state(cookies) <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Easy to use but max 4kb and user can disable them
    :star: Hidden state (info is hidden) <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> May declare hidden fields in form. But it is a performance killer as all pages must be contained in a form
    :star: Server side state (store info in database) <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> safe but may take some time to query the db
    :ocean: Typically all of them are used at same time for diff purposes
  
#  Normal forms and physical database design :lizard:
  
  
* Normalization <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> a technique of organizing data in multiple related tables minimizing data redundancy (Problems: may inc db size, insertion/deletion/updation problems) 
* 1st Normal form <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Scalable table easily extendable.
    :cloud: Each column should have atomic values (not like a.b)
    :cloud: A col should contain values of same type
    :cloud: Each col should have a unique name
    :cloud: The order in which the data is stored does not matter
* 2nd Normal form <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/>  No partial dependencies
    :rose: eliminate functional dependecies on a partial key
    :rose: Put the field in a separate table from those dependand on the whole key
* 3rd Normal form <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> No transitive dependecy
    :star: An attr depends in an attr that is not a prim key
    :star: Take both these attr's in a separate table
* Boyce - Codd normal form (BCNF) <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> For any dependency A -> B, A should be a super key, A cannot be non'prime if B prime
    :knife: Break table again
    :knife: Only key -> non-key constraints left
* Probs with decom
    1. Some queries bcome expensive
    1. May not be able to reconstruct origin relation
    1. Checking some dependencies may require joining the decomped rels
* Indexing
    :shit: Hash indeces only good for equality search
    :poop: Sorted files and tree indeces best for range search
    :shit: Files rarely kept sorted in practice, Binary tree
  
#  Transactions :shark: 
  
* An abstract view of a user program: a sequence or read and writes that execute as a unit
A <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Atomic (all actions completed or none)
C <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Consistent (after commit/abort data satisfies IC)
I <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Isolation (changes not visible to other TAs until commit)
D <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Durable (nothing lost in future, failure occuring after commit cause no loss of data)
* We need to schedule TAs
    :icecream: Serial <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> schedule does not interleave actions of diff TAs
    :icecream: Equivalent schedules <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> The effect of exec the 1st schedule is identical to executing the effect of 2nd schedule.
    :icecream: Serializable <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> sched equivalent to some serial exev of TAs
* Lock based Concurrency control (si mutex)
    :lollipop: Shared lock <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> if a TA has this key, it can read but not update 
    :lollipop: Exclusive lock <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> If TA has this key, it can both read and update
* The log
    :cake: Records all TA actions, using TA id, so easy to undo specific TA is abort
  
#  Web service Protocols :eagle:
  
* Html
    :sunny: GET, POST, PUT, DELETE requests
    :sunny: GET params in url text
    :sunny: POST params in msg body
* REST
    :cloud: URI defines resource being requested <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> easy to follow
    :cloud: Relies on for basic operations: (GET query, POST add, PUT update, DELETE delete) Small prob -> No support for put and delete requests
* AJAX
    :fire: method to send and receive data in the background without refreshing the webpage. It uses XMLHttpRequest obj.
  
#  Security :bird:
  
* 3 definitions
    :icecream: Secrecy <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Users should not see what they aren't supposed to
    :icecream: Integrity <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> They should not modify what they aren't supposed to.
    :icecream: Availability <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> They should see and modi what they are allowed to.
* For acces over the network <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> ***Encryption***
    :owl: Symmetric <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> same key to enc and decr
    :owl: Public-key <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Encription key public, decr key secret
* SSL (secore socket layer) & SET (secure electronic transaction) Protocols
    :ocean: https is http over ssl
* Authenticating users
    :candy: Simple password auth
    :candy: Digital signatures <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> I enc the order with my private key and then with Amazon's public key, Amazon decr first with their private key and then my public key.
* Email security
    :boat: Encr them
* Database access ctrl
    :star: Discretionary access ctrl
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :snowflake: Creator has all privilages over table and  can assign it to others.
    ```sql
    GRANT ( SELECT | INSERT | DELETE | REFERENCES)
        ON object TO users [WITH GRANT OPTION]
    // WITH GRANT OPTION allow the user 
    // to pass privilage to other users
    ```
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :snowflake: Role based auth (only admin has this, director has smth else)
    :star: Mandatory access ctrl 
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :snowflake: Based on system-wide policies that can't be changed by individual users <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Each DB Obj is assigned a *security class*, each subject is assigned a *clearance* and there are rules based on classes and clearance ctrl who can read write. This protects from trojan horse problems
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :snowflake: Bell-LaPadula Model
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/>  :fire: Assign a class to each subj(user) and each obj. Classes are <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/>  <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> (TopSecret > Secret > Confidential > Unclassified)
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :fire: S can read O iff class(S) >= class(O)
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :fire: S can write in O iff class(S) <= class(O)
* Example attacks <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> SQL injection
  
#  NoSQL & NewSQL :dolphin: 
  
* Structural Variety in Big data
    :o: Sets
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :knife: set of key+value, like a large hash table, ex Cassandra
    :o: Hierarchies
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :knife: Like key value but value is a complex doc, adds search functionality  in doc. Ex: MongoDB, CouchDB
    :o: Graphs 
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :knife: Model is a labeled, directed? multi graph. Used for social medias
    :o: Arrays
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :knife: Can be massive n-D arrays
* RDBMS provides ACID and strong Cons over avail under partition, Cassandra BASE weak consistency, availab and Part tol
* CAP theorem: A distr system can satisfy at most 2 out of
    * Consistency <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> All nodes have same data anytime
    * Availability <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Sys allows operations all time
    * Partition-tolerance <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> sys continues to work despite network partitions
* NoSQL <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> sacrificing functionality for performance
* NewSQL <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> SQL with enhanced performance architectures
  
#  Process XML: XPath, XQuery :sagittarius:   
  
* XML
    :aries: Modeled as tree, graph
    :aries: Query using XQuery
* XPath
    :taurus: //smth <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> for finding smth wherever it is
    :taurus: //div/li/a <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> for each div no matter where go to li child than a grandchild
    :taurus: //li[@class="heh"] <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> all li's with class heh
    :taurus: (self | child | parent | descendent | descendend-or-self | ancestor | ancestor-or-self | following | preceding | following -sibling | preceding-sibling ) :: ul[1] <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> take first ul for whatever axis specified. 
    :taurus: //[contains(text(), "Content")] te gjithe me Content brenda si txt ose //cd[price < 19]
  
* XQuery
    :aquarius: Xquery is as SQL to db
``` c
FOR $x IN document("bib.xml")/bib/book
WHERE $X/year > 2000 AND count($x) > 1
RETURN $x/title
  
FOR $x IN document("bib.xml")/bib/book
RETURN <result> $x </result>
  
LET $x IN document("bib.xml")/bib/book
RETURN <result> $x </result>
  
<big_pubs>
    FOR $p IN distinct(document("bib.xml")//publisher)
    LET $b = document("bib.xml")/book[publisher = $p]
    WHERE count($b) > 100
    RETURN $p
</big_pubs>
  
(FOR-LET) > WHERE > ORDERBY-RETURN
```
  
#  RDF & SPARQL   :koala: 
  
  
* RDF <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> resource description framework 
    :moon: framework for describing resources on the web
    :moon: model for data and a syntax <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Query lang SPARQL
    :moon: indep of XML, RDF data may never occur in XML form
    :moon: All data expressed in triples
    <img src="https://latex.codecogs.com/gif.latex?&#x5C;quad"/> :rocket: Subject <img src="https://latex.codecogs.com/gif.latex?&#x5C;xrightarrow{Predicate}"/> Object
* SPARQL <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> used to query data in RDF
    :crocodile: First put the PREFIXES
    :crocodile: Use ? for what you want to select. (?x wildcard for anonymous node)
    For the following data:
```bash
@prefix foaf: <http://xmlns.com/foaf/0.1/> .
_:a foaf:name "Johnny Lee Outlaw" . 
_:a foaf:mbox <mailto:jlow@example.com> .
_:b foaf:name "Peter Goodguy" .
_:b foaf:mbox <mailto:peter@example.com> .
  
```
```c
PREFIX foaf: <http://xmlns.com/foaf/0.1/>
SELECT ?name ?mbox
WHERE 
    { 
        ?x foaf:name ?name. 
        ?x foaf:mbox ?mbox
    }
```
  
#  Big Data :octopus: 
  
* 4V-s of Big Data
    :bee: Volume (it is huge)
    :bee: Velocity <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> the frequency of incoming data needing to be processed 
    :bee: Variety (self explanatory)
    :bee: Veracity <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> Trustworthiness of data
  
  
  
#  MapReduce :peach:
  
* Concept
    :pear: Map <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> split the inputs among a bunch of machines
    :pear: Shuffle <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> sort keys so that the reduce state gets the same key for same machine
    :pear: Reduce <img src="https://latex.codecogs.com/gif.latex?&#x5C;rightarrow"/> takes the result from the machines and combines them tgether to get the result we are looking for
* Hadoop :elephant:
    :grapes: MapReduce implementation in Java 
    :grapes: Uses a scalable, fault tolerant distributed file system
    :grapes: Chunks of 64 MB
    :grapes: All intermediate data communicated via disk
    :grapes: Task scheduler: central point of failure
* Spark
    :watermelon: Inherits Hadoop Distributed File System
    :watermelon: MapReduce from Hadoop
    :watermelon: But, instead of Java it uses Scala and instead of disk-based comm uses in-memory comm
  
