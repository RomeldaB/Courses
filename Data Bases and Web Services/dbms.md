# :heart: Data Bases and Web Services
# Database design :butterfly:
* Conceptual $\longrightarrow$ construct description of info disregarding tech.
* Logical $\longrightarrow$ construct descr based on specific data model w/o implementation.
* Physical $\longrightarrow$ perform implementation using particular dbms.

#### Conceptual :spider:
* Entity $\longrightarrow$ real world obj distinguishable from others.
* Entity set$\longrightarrow$ collection of similar entities (Employees). They have attributes, and keys.
* Relationship $\longrightarrow$ association among 2+ entities.
* Relationship set $\longrightarrow$  collection of similar relationships.
* Constraints 
    :moon: Multiplicity $\longrightarrow$ how many entities can participate in a rel.
    :moon: Participation $\longrightarrow$ Ent set is total if all entities participate in the rel. Partial if some don't.
* Weak entity $\longrightarrow$ Identified uniquely only by considering primary key of the owner entity
    :hole: Owner - weak ent must be in 1:n rel
    :hole: Weak ent must have total participation in the rel
* ISA hierarchy $\longrightarrow$  same as inheritance
* Aggregation $\longrightarrow$ considering a relationship as an entity OR relationship involving a relationship set.
* (Ndoshta s'eshte) **UML** $\longrightarrow$ Class model at the core of OO dev and design. An instance is like an entity and the class as the set.

# Relational Model (Logical) :bug:
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
* Integrity constraints $\longrightarrow$ condition that must be true for any instance of the database. Specified when shema defined and are checked when relations are modified.

* Primary key $\longrightarrow$ no 2 diff tuples have same value of this field. This may not be true for any subset of the key. If part 2 false $\rightarrow$ **superkey**

* Foreign key $\longrightarrow$ A field (set of fields) that is used to refer to a tuple in another relation. It must correspond to the prim key of the second relation

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

* Referential integrity $\longrightarrow$ Default is NO ACTION, other values include CASCADE, SET NULL or SET DEFAULT.

* When translating ISA to tables (3 ways)
    :cake: Separate tables(relation) for each ent set
    $\quad$    * Must use delete cascade
    $\quad$    * Queries involving all employees easy
    $\quad$    * Those involving just a specific one require join to get some attributes
    :cake: 2 relations (only the specific ones)
    $\quad$    * Each emplyee(for ex) must be in one of the 2
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

# Relational Algebra :rabbit:
* Selection $\sigma_{gpa<4}$  $\longrightarrow$ select based on a condition
* Projection $\pi_{name,login}$  $\longrightarrow$ select only specified attributes in the specified order
* Cartesian product $\longrightarrow$ We know this
* Natural join $R_1 \bowtie_{bid} R_2$  $\longrightarrow$ Equate attrubutes of same name. Project out redundant attr
* Query $\longrightarrow$ {S | S $\in$ Sailors logical_and S.rating > 8}

#### Relational algebra vs calculus
:carrot: Rel alg is a set-based formalization of selection, projection, cross product (no aggregation!)
:carrot: Relational calculus is expressed in predicate logic.

:carrot: Relational algebra is operation oriented i.e. it states the procedure to follow to compute a result
:carrot: Relational Calculus is declarative i.e. it allows us to declare the answer without being explicit about how they are c
computed

:hibiscus: Both Relational Algebra and Relational Calculus have equal expressive power. 

# Query processing :snake:
* The order is $\longrightarrow$ From, where, group by, having, select, order by.
```sql
SELECT *
FROM Bla
WHERE Bla.m = 7
GROUP BY Bla.rating
HAVING Count(*) > 1
ORDER BY Bla.rating
```
* Query is parsed into a relational algebra expr 
    :cucumber: SELECT as $\pi$
    :cucumber: FROM as X
    :cucumber: WHERE as $\bowtie$ OR $\sigma$ depending if it references one or 2 tables.
    :cucumber: Views are expanded and flattened
* Logical Plan created (Logical query tree)
* Logical plan is optimized (heuristic optimization) and turned to physical
    :tomato: Logical tree into more efficient logical tree
    :tomato: ex. push all predicates down
* Physical plan optimized(cost-based optimization) then execution
    :carrot: Ideally find best plan, practically avoid worst plans
* Summary 
    * Query tree $\rightarrow$ internal representation of query
        :lemon: Logical tree based on relational algebra
        :lemon: Physical tree based on concrete algorithms
    * Optimization $\rightarrow$ modify tree to perform
        :lemon: Logical opt $\rightarrow$ query rewriting
        :lemon: Physical opt $\rightarrow$ black magic
# Database app dev :sheep:
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

# Web services :elephant:
* Each comp has world wide unique id:
    :avocado: IP address (32 bit IPv4 and 128 in IPv6)
    :avocado: Domain name: subdomain.host.top-level-domain
    :avocado: Domain Name Server to resolve
* Uniform Resource Identifiers (http://www.dabadaba.com/index.html)
    :pineapple: Naming scheme (http)
    :pineapple: Name of host comp + optional port nr (.com:80)
    :pineapple: Name of resource (index.html)
    :pineapple: Uniform Resource Locater subset of it
    $\quad$ :lemon: Used for identification via location
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
* Document Object Model $\rightarrow$ platform and language neutral interface that allows programs and scripts to dynammically access and update content and structure of HTML docs

# 3-Tier Architecture :fish:
1. Presentation
    :cloud: The user interface
    :cloud: Needs to adapt to screen size
1. Application logic
    :cloud: Implement bussines logic
    :cloud: Access to dbms
1. Data management
    :cloud: \>=1 dbms
* Clients
    * Thin $\rightarrow$ Client implements 1 and Server 2,3
    * Thick $\rightarrow$ Client implements 1,2 and server 3
        :sunny: Do not scale
* Single tier arch
    * Server does all
    * Adv $\rightarrow$ easy to maintain
    * Des $\rightarrow$ User expects UI
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
    :star: Client-side state(cookies) $\rightarrow$ Easy to use but max 4kb and user can disable them
    :star: Hidden state (info is hidden) $\rightarrow$ May declare hidden fields in form. But it is a performance killer as all pages must be contained in a form
    :star: Server side state (store info in database) $\rightarrow$ safe but may take some time to query the db
    :ocean: Typically all of them are used at same time for diff purposes

# Normal forms and physical database design :lizard:

* Normalization $\rightarrow$ a technique of organizing data in multiple related tables minimizing data redundancy (Problems: may inc db size, insertion/deletion/updation problems) 
* 1st Normal form $\rightarrow$ Scalable table easily extendable.
    :cloud: Each column should have atomic values (not like a.b)
    :cloud: A col should contain values of same type
    :cloud: Each col should have a unique name
    :cloud: The order in which the data is stored does not matter
* 2nd Normal form $\rightarrow$  No partial dependencies
    :rose: eliminate functional dependecies on a partial key
    :rose: Put the field in a separate table from those dependand on the whole key
* 3rd Normal form $\rightarrow$ No transitive dependecy
    :star: An attr depends in an attr that is not a prim key
    :star: Take both these attr's in a separate table
* Boyce - Codd normal form (BCNF) $\rightarrow$ For any dependency A -> B, A should be a super key, A cannot be non'prime if B prime
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

# Transactions :shark: 
* An abstract view of a user program: a sequence of read and writes that execute as a unit
A $\rightarrow$ Atomic (all actions completed or none)
C $\rightarrow$ Consistent (after commit/abort data satisfies IC)
I $\rightarrow$ Isolation (changes not visible to other TAs until commit)
D $\rightarrow$ Durable (nothing lost in future, failure occuring after commit cause no loss of data)
* We need to schedule TAs
    :icecream: Serial $\rightarrow$ schedule does not interleave actions of diff TAs
    :icecream: Equivalent schedules $\rightarrow$ The effect of exec the 1st schedule is identical to the effect of executing the 2nd schedule.
    :icecream: Serializable $\rightarrow$ sched equivalent to some serial exec of TAs
* Lock based Concurrency control (si mutex)
    :lollipop: Shared lock $\rightarrow$ if a TA has this key, it can read but not update 
    :lollipop: Exclusive lock $\rightarrow$ If TA has this key, it can both read and update
* The log
    :cake: Records all TA actions, using TA id, so easy to undo specific TA is abort

# Web service Protocols :eagle:
* Http
    :sunny: GET, POST, PUT, DELETE requests
    :sunny: GET params in url text
    :sunny: POST params in msg body
* REST
    :cloud: URI defines resource being requested $\rightarrow$ easy to follow
    :cloud: Relies on 4 basic operations: (GET query, POST add, PUT update, DELETE delete) Small prob -> No support for put and delete requests
* AJAX
    :fire: method to send and receive data in the background without refreshing the webpage. It uses XMLHttpRequest obj.

# Security :bird:
* 3 definitions
    :icecream: Secrecy $\rightarrow$ Users should not see what they aren't supposed to
    :icecream: Integrity $\rightarrow$ They should not modify what they aren't supposed to.
    :icecream: Availability $\rightarrow$ They should see and modi what they are allowed to.
* For acces over the network $\rightarrow$ ***Encryption***
    :owl: Symmetric $\rightarrow$ same key to enc and decr
    :owl: Public-key $\rightarrow$ Encription key public, decr key secret
* SSL (secore socket layer) & SET (secure electronic transaction) Protocols
    :ocean: https is http over ssl
* Authenticating users
    :candy: Simple password auth
    :candy: Digital signatures $\rightarrow$ I enc the order with my private key and then with Amazon's public key, Amazon decr first with their private key and then my public key.
* Email security
    :boat: Encr them
* Database access ctrl
    :star: Discretionary access ctrl
    $\quad$ :snowflake: Creator has all privilages over table and  can assign it to others.
    ```sql
    GRANT ( SELECT | INSERT | DELETE | REFERENCES)
        ON object TO users [WITH GRANT OPTION]
    // WITH GRANT OPTION allow the user 
    // to pass privilage to other users
    ```
    $\quad$ :snowflake: Role based auth (only admin has this, director has smth else)
    :star: Mandatory access ctrl 
    $\quad$ :snowflake: Based on system-wide policies that can't be changed by individual users $\rightarrow$ Each DB Obj is assigned a *security class*, each subject is assigned a *clearance* and there are rules based on classes and clearance ctrl who can read write. This protects from trojan horse problems
    $\quad$ :snowflake: Bell-LaPadula Model
    $\quad$ $\quad$  :fire: Assign a class to each subj(user) and each obj. Classes are: TopSecret > Secret > Confidential > Unclassified
    $\quad$ $\quad$ :fire: S can read O iff class(S) >= class(O)
    $\quad$ $\quad$ :fire: S can write in O iff class(S) <= class(O)
* Example attacks $\rightarrow$ SQL injection

# NoSQL & NewSQL :dolphin: 
* Structural Variety in Big data
    :o: Sets
    $\quad$ :knife: set of key+value, like a large hash table, ex Cassandra
    :o: Hierarchies
    $\quad$ :knife: Like key value but value is a complex doc, adds search functionality  in doc. Ex: MongoDB, CouchDB
    :o: Graphs 
    $\quad$ :knife: Model is a labeled, directed? multi graph. Used for social medias
    :o: Arrays
    $\quad$ :knife: Can be massive n-D arrays
* RDBMS provides ACID and strong Cons over avail under partition, Cassandra BASE weak consistency, availab and Part tol
* CAP theorem: A distr system can satisfy at most 2 out of
    * Consistency $\rightarrow$ All nodes have same data anytime
    * Availability $\rightarrow$ Sys allows operations all time
    * Partition-tolerance $\rightarrow$ sys continues to work despite network partitions
* NoSQL $\rightarrow$ sacrificing functionality for performance
* NewSQL $\rightarrow$ SQL with enhanced performance architectures

# Process XML: XPath, XQuery :sagittarius:   
* XML
    :aries: Modeled as tree, graph
    :aries: Query using XQuery
* XPath
    :taurus: //smth $\rightarrow$ for finding smth wherever it is
    :taurus: //div/li/a $\rightarrow$ for each div no matter where go to li child than a grandchild
    :taurus: //li[@class="heh"] $\rightarrow$ all li's with class heh
    :taurus: (self | child | parent | descendent | descendend-or-self | ancestor | ancestor-or-self | following | preceding | following -sibling | preceding-sibling ) :: ul[1] $\rightarrow$ take first ul for whatever axis specified. 
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

# RDF & SPARQL   :koala: 

* RDF $\rightarrow$ resource description framework 
    :moon: framework for describing resources on the web
    :moon: model for data and a syntax $\rightarrow$ Query lang SPARQL
    :moon: indep of XML, RDF data may never occur in XML form
    :moon: All data expressed in triples
    $\quad$ :rocket: Subject $\xrightarrow{Predicate}$ Object
* SPARQL $\rightarrow$ used to query data in RDF
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

# Big Data :octopus: 
* 4V-s of Big Data
    :bee: Volume (it is huge)
    :bee: Velocity $\rightarrow$ the frequency of incoming data needing to be processed 
    :bee: Variety (self explanatory)
    :bee: Veracity $\rightarrow$ Trustworthiness of data

# ***Ficken*** rasdaman!! bitte!!!

# MapReduce :peach:
* Concept
    :pear: Map $\rightarrow$ split the inputs among a bunch of machines
    :pear: Shuffle $\rightarrow$ sort keys so that the reduce state gets the same key for same machine
    :pear: Reduce $\rightarrow$ take the result from the machines and combine them together to get the result we are looking for
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

:eggplant: :cherries: :melon: :tropical_drink: :beer: :fireworks: :cocktail: :ring: :wedding: :wine_glass: :hamburger: :taco: :pizza: :popcorn: :corn: :peanuts: :kiwi_fruit: :tangerine: :hibiscus: :desert: :palm_tree: :four_leaf_clover: :cactus: :evergreen_tree: :deciduous_tree: :herb: :chipmunk: :hamster: :panda_face: :rhinoceros: :monkey: :gorilla: :hand: :earth_africa: :earth_asia: :milky_way: :comet: :world_map: :euro: :dollar: :volcano: :rocket: :crescent_moon: :full_moon: :new_moon: :first_quarter_moon: