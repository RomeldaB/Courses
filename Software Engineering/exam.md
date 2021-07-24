## Software Engineering Exam Preparation

#### What is Software Engineering:
▶️ The engineering discipline concerned with all aspects of software production
* Multi-person construction of multi-version software
* Adherence to quality standards
* Offers theory, organisation, management, methods, techniques, tools for large program systems
* Practice that often does not fit a theory

#### Software
* Computer programs + assosiacted documentation
* Software products may be: 
    * Generic - developed to be sold to a range of different customers
    * Bespoke (custom) - developed for a single customer according to their specification

**System** ▶️ purposeful collection of inter-related components working together to achieve some common objective. 

**Categories:**
▶️ Technical computer-based systems
```
- not self aware
- include hardware & software, operators and operational processes are not normally considered as part of the system
```
▶️ Socio-technical systems
```
- technical systems + operational processes & people who use & interact with t.s.
```
**Software industry almost always tasked with socio-technical systems**

**Characteristics of socio-tech systems:**
* Emergent properties (properties of the system as a whole that depend on components and their relationships)
```
Examples:
volume, reliability, security, repairability, usability
```
* Non-deterministic (not always same otput for same input, partially dependent on human operators, time-varying environment)
* Copmlex relationships with organisational objectives (they are not dependent only on the system)

#### The software lifecycle

**Requirements Engineering** ▶️ The process of eliciting:
1. the services that the customer requires from a system 
2. the constraints under which it operates and is developed

**Schematic procedure** ▶️ inception (ask questions), elaboration, negotiation, requirements management

**Requirements** ▶️ descriptions of the system services and constraints that are generated during the requirements engineering process
▶️**Types:**
1. User requirements
    * statements in natural language + diagrams of the system's services and its operational constraints
    * must be understandable by users who don‘t have detailed technical knowledge
    * defined using natural language, tables and diagrams - danger of lack of clarity and precision, requirements confusion and amalgamation => solution: UML
    * read by client managers, system end-users, client engineers, system architects
2. System requirements
    * a structured document setting out detailed descriptions of the system's functions, services and operational constraints
    * defines what should be implemented so may be part of a contract between client and contractor
    * read by: system end-users, client engineers, system architects, software developers

**Specification techniques**
```
* natural language (lack of modularisation, over-flexible)
* structured language specifications (standard templates, limited terminology)
* form-based spec. (predefined items -> guidance for completeness)
* description languages/formal spec. (consice, unsuitable for customers)
* graphical models
```
1. **Functional requirements** ▶️ statements of services the system should provide, how the system should behave
2. **Non-functional requirements** ▶️ define sys properties (reliability, response time, storage) and constraints (I/O device capability, securty, legal impact, domain expert workflow)
3. **Domain req** ▶️ req that come from the application domain of the sytems that reflect characteristics of that domain

##### Requirements Document = user req + system req, not a design document, customer language used, adopting your company's convention for the req
___
#### UML
▶️ The Unified Modeling Language is the standard language for specifying, visualizing, constructing, and documenting all the artifacts of a software system.
▶️ Main diagram types:
```
1. Use Case Diagram (functional)
2. Activity/Action Diagram (behavioural)
3. Class Diagram (structural)
4. State Diagram (behav.)
5. Sequence Diagram (behav.)
6. Other: Object, Collaboration, Package, Deployment, Interaction Diagrams
```
**Use Case Diagrams**
* *use case* ▶️ chunk of functionality, not a software module (shuold contain a verb in its name)
* *actor* ▶️ someone/thing interacting with system under development (rle in scenario)
* visualize relationships btw the two
* capture high-level alternate scenarios to get early customer agreement
(person-circle representation)

![](https://www.uml-diagrams.org/use-case-diagrams/use-case-diagram-elements.png)

____

**Activity Diagrams**
* Represents the overall flow of control
* Graphical workflow of activities and actions (flow-chart with user 0perceived actions)
* *Swimlanes* - dashed line separating two roles

![](https://home.iscte-iul.pt/~hro/RUPSmallProjects/core.base_rup/guidances/supportingmaterials/resources/activity20.gif)

___

**Class Diagrams**
* *Class* ▶️ collection of objects with common structure, behaviour, relationships, and semantics
* Displayed as box with up to 3 compartments: name, list of attributes (state variables), list of operations
* Class modeling elements:
    * classes with structure + behaviour
    * relationships
    * multiplicity and navigation indicators
    * role names

***Relationships:*** models that 2 objects can "talk"
* Association ▶️ bi-directional connection between classes
* Aggregation ▶️ stronger form ("has a"), rel btw a whole and its parts
* Depedency ▶️ weaker form

***Multiplicities, Navigation:***
* Multiplicity numbers & intervals denote number of instances that can/must participate in relationship instance (0..1 - may have one, 1 - must have one, 0..* or * - may have many, 1..* - has at least one)
* Arrow head to denote: traversable only this direction

***Inheritance:*** relation between subclass and superclass
* Sublass instances have all properties specified in superclass, plus the specific ones defined within
* Also called "is-a"

![](https://www.uml-diagrams.org/examples/class-diagram-example-hasp-licensing-domain.png)

___

**Sequence Diagrams**
* Display object interactions arranged in a time sequence
* Can be from user's perspective, useful for designer and customer
* How many SDs: 
    * For every basic flow of every use case
    * For high-level, risky scenarios

![](https://online.visual-paradigm.com/repository/images/2bb15308-e5e3-4a67-acaf-6e40cdc8d1fb.png)

▶️ Compared to activity diagrams:
* Granularity:
    * Act: user-perceived actions
    * Seq: actors+system components
* Emphasis on:
    * Act: internal state transitions
    * Sys: component interaction

___

*State Transition Diagrams*
* Show life history of a given class
* Use for classes that typically have a lot of dynamic behaviour

![](https://www.uml-diagrams.org/state-machine-diagrams/protocol-state-machine-diagram-overview.png)

___

**Model-Driven Architecture MDA**
* Infrastructure: core of architecture, profiles, stereotypes
* Superstructure: static & dynamic model elements
* Object Constraint Language (OCL): formalize assertions, rules
* Diagram Interchange: UML exchange format

*Vision:*
UML spec ▶️ PIM (platform-indep model) ▶️ PSM (target model) ▶️ implementation

**DSLs**
* Alternative to UML: domain-specific modelling languages
    * UML considered too complex, software biased
* Rule of thumb:
    * UMLs better for enterprise apps(millions of possible directions)
    * DSLs better for embedded systems (slearly delimited app domain & paths)

#### Design Patterns

*Semiotics:* Aspects of Language Use
* Syntax (grammar - how to write it)
* Semantics (what to express, how it is evaluated)
* Pragmatics (how to apply)
* Meta language (describe the language of discourse)

*pattern* ▶️ description of the problem and the essence of its solution, abstract to be reused, should rely on objectcharacteristics
*design pattern* ▶️ way of re-using abstract knowledge about a design problem and its solution

**Pattern elements**
```
* Name (a meaningful pattern identifier)
* Description
* Problem / Applicability description
* Solution description (not concrete design but template for design solution)
* Consequences (results and trade-offs of applying the pattern)
```
#### Different patterns:
**1. Singleton**
* Desc: ensure a class has only one instance and provide a global point of access to it
* Appl: used when only one object of a kind may exist in the sys
* Sol: 
    * defines an Instance class operation that lets clients access its unique instance
    * responsible for creating and maintaining its own unique instance

**2. Observer**
* Desc: separated the display of object state from the object itself
* Appl: used when multiple displays of state are needed
* Sol: UML descr in slides
* Conseq: Optimizations to enhance display performance are impractical

**3. Mediator**
* D: define an object that encapsulates how a set of objs interact
    * promotes loose coupling by keeping objects from referring to each other explicitly
* A: complex interaction exists
* Conseq: 
    * limits subclassing
    * decouples colleagues
    * simplifies object protocols
    * abstracts how objects cooperate
    * centralizes control

**4. The Façade**
* D: provides a unified interfae to a set of interfaces in a subsystem, defines a higher-level interface that makes subsystem easy to use
* Applicability:
    * need to provide a simple interface to complez sys
    * need to decouple a subsystem from its clients
    * need to provide an interface to a software layer

* Conseq:
    * Shields clients from subsystem components
    * Promotes weak coupling between the subsystem and its clients

**5. The Proxy**
* D: provide a surrogate or placeholder for another object to control access to it
* Problem / Applicability:
    * Remote proxies can hide the fact that a real object is in another address space 
    * Virtual proxies can create expensive objects on demand
    * Protection proxies can control access to an object
    * Smart references can perform additional action above a simple pointer

**6. Adapter**
* D: adapter lets classes work together that could not otherwise because of incompatible interfaces
* Appl:
    * Need to use an existing class whose interface does not match
    * Need to make use of incompatible classes
* C: class adapter commits to the concrete Adapter class

**6. Composite**
* Def:
    * Compose objects into tree structures to represent part-whole hierarchies
    * Composite lets clients treat individual objects and compositions of objects uniformly
* A: any time there is partial overlap in the capabilities of objects

#### Types of Patterns

▶️ **Creational**
• Abstract Factory - Creates an instance of several families of classes
• Builder - Separates object construction from its representation
• Factory Method - Creates an instance of several derived classes
• Prototype - A fully initialized instance to be copied or cloned
• Singleton - A class of which only a single instance can exist 

▶️ **Structural**
• Adapter - Match interfaces of different classes
• Bridge - Separates an object’s interface from its implementation
• Composite - A tree structure of simple and composite objects
• Decorator - Add responsibilities to objects dynamically
• Façade - A single class that represents an entire subsystem
• Flyweight - A fine-grained instance used for efficient sharing
• Proxy - An object representing another object

▶️ **Behavioral Patterns**
• Chain of Resp. - A way of passing a request between a chain of objects
• Command - Encapsulate a command request as an object
• Interpreter - A way to include language elements in a program
• Iterator - Sequentially access the elements of a collection
• Mediator - Defines simplified communication between classes
• Memento - Capture and restore an object's internal state
• Observer - A way of notifying change to a number of classes
• State - Alter an object's behavior when its state changes
• Strategy - Encapsulates an algorithm inside a class
• Template Method - Defer the exact steps of an algorithm to a subclass
• Visitor - Defines a new operation to a class without change

___

#### Compiling and Linking C/C++ programs

##### Preprocessor
▶️ Defines commonly used constants, code fragments etc.
▶️ Used also for conditional compilation
▶️ No semantics as in C syntax
▶️ Some directives:
```C
#include
#define
#if / #ifdef
...
```
▶️ USE PARENTHESES! 
```C
ex: #define mult(a,b) ((a)*(b))
```
##### Compiler
▶️  Generates (relocatable) machine („object“) code from source code
▶️  OS (with HW support) uses this to implement user address space:
* Actual main memory address = base address + relative address
* Base address kept in segment register, added dynamically by CPU
* Security: program cannot access base register ("priviledged mode"), hence cannot address beyond its segment limits

**Object files** ▶️ Contain code from a program fragment (machine code, constants, size of static data segments,...)

**External Func and Vars**
▶️ Cross module addressing rules:
* no modifier = locally allocated, globally accessible
* static = loca alloc, loc access
* extern = allocated in other compilation unit

**Name Mangling** ▶️ compiler modifies names to make them unique (prefix/suffix)
*Code compiled with different compilers is incompatible!!*

**The Linker/Loader**
▶️ Task: generate one executable file from several object and library files
```
• Read object files
• Resolve addresses from (relocatable) code
• Link runtime code (start/exit handling!)
• Add all code needed from libraries
• If required: establish stubs to dynamic libraries
• Write executable code into file, set magic number, etc
```

**Strip**
▶️ Default: executable contains symbol tables (func names, addresses, parametrization...)
▶️ Disadvantages:
* allows reverse engineering
* substantially larger code files
▶️ Before shipping: strip executables
```bash
file filename
strip filename
```

**Libraries**
▶️ An archive file containig a collection of object files (classes, modules...)
* Object files vs Libraries:
    * Object file linked in completely, from library only what is actually needed
* Static vs Dynamic
    * Static - code is added to the executable, just like object file; not needed after linkage
    * Dynamic - only stub linked in, runtime system loads; needed at runtime (version!)
* Naming conventions (Linux)
```bash
Static libraries: libxxx.a
Dynamic libraries: libxxx.so
link with: ld ... –lxxx
```

*Dynamic libraries*
▶️ Found using:
```bash
LD_LIBRARY_PATH variable
similar to PATH: set before program start
```
▶️ Know about use:
```bash
$ ldd filename
```

##### Schematic program run:
▶️ OS
* Open file
* Look at first page: magic number, segment sizes, etc.
* Allocate segments (code, runtime stack, heap, ...)
* Read code file into code segment
* Set up process descriptor (external resources, limits, ...)
* Pass control to this process
* Handle system calls
* Terminate program, free process slot and resources

▶️ Application program:
* Set up runtime environment
(argv/argc, ...)
* Call main()
* On system calls, interrupts, etc.: pass control to OS
* Upon exit(), or main()‘s return, or a forced abort: clean up (close file descriptors, sockets, ...), pass back to OS

**Summary**
*To create executable program, you must perform:*
* Preprocess– textually expands definitions, condition-guarded code pieces
* Compile – translates source code into relocatable machine code („object code“)
* Link – bind object files and archives into executable program

<h4 style="color: darkblue">Defensive Programming</h4>
▶️ intends "to ensure the continuing function of a piece of software in spite of unforeseeable usage of said software"
=> practises to avoid bugs upfront
▶️ defending against errors
▶️ good design yields better product and should be evident in code (key checkpoints)

**Invariants**
* Conditions that do not vary (design mileposts of code)
* Types:
    * Loop invariants
    ```
    - Part of program correctnes proofs
    - Often conceptual
    - Must be commented instead of tested
    ```
    * Class invariants
    ```
    - All constructors should place their object in a valid state
    - All methods should leave their object in a valid state
    (guaranteed by pre- and post-conditions)
    ```
    * Method invariants
    ```
    - "Design by Contract"
    - Methods are contracts with the user
    - Users must meet pre-cond. of the method
    - Method guarantees post-cond.
    ```
    * ... plus plain old invariants
___
* Enforcing Invariants (error handling):
    * *assertions* = force-terminate program (errors that don't depend on end user, non-public memeber func.)
    ```C
    assert() macro
    for flase argument =>
        - prints expression, file, line nr
        - calls abort()
    - Can turn off with NDEBUG
    Never ever use it in a server!!!
    ```
    * *exceptions* = break flow of control (*goto*) - for preconditions on public member func.
    ```C++
    - Interrupt regular flow of control
    - Ripple up calling hierarchy
    - They are classes, can have params
    - throw() instantiates exception object
    - Can have multiplt catch() sensitive to any excep type
    ```
    * *return codes* = data-oriented, keep flow of control (post-cond. usually a method's output)
    ```
    - Methods have a return parameter
    - For otherwise void result, it carries only success information
    - If method has regular result: reserve otherwise unused value
    - It is an interface property
    - Strongly recommended for single-return functions
    ```
___
**Structured Programming**
* Component-level design technique [Dijkstra et al] which uses only small set of programming constructs
* Principle: building bocks to enter at top & leave at bottom
    * Good: sequence(“;“); condition; repetition
    * Bad: (computed) goto; break; continue;...
* Advantage: less complex code => easier to read + test + maintain

*Unstructured loops* ▶️ mainly abolished by banning GOTO (Apple fail)

**Software Crisis**
▶️ Early CS: difficulty of writing useful & efficient computer programs in the required time
▶️ Reasons:  rapid increases in computer power, complexity of problems that could be tackled
▶️ Conseq: Over budget, over time, ineffiecient... projects
▶️ **Response** 
    => Structured Programming 
    => Object-oriented prog. later
    => Defensive prog.
    => Academia contributed correctnedd proofs
    => Systematic testing

**Code Guides** ▶️ set of rules to which programmers must adhere (within company or project)
* Twofold purpose: have uniform style (better learning for new members), codify best practice (what is acknowl. to be advantageous)
* Core Coding Rules:
```
- Reflect before typing
- Be pedantic (make it foolproof, document)
- Design cost-aware
```

<h4 style="color: darkred">Configuration, Version, Release Management</h4>
▶️ Symptoms of the Change Chaos
* Problems of identification and tracking
* Problems of version selection
* Software delivery problems

*Software* *Configuration* *Management* **SCM** ▶️ the discipline of controlling the evolution of software systems (indispensable for large, long-lived software)

**3 Classic CM Problems**
* The double maintainance problem
(prevent the occurrence of multiple copies of the same file that must be independently updated)
* The shared data problem
(allow two or more developers with access to the same file/data)
* The simultaneous update problem
(prevent file clobbering from two developers updating the same file at the same time)

*Change cycle:*
1. checkout
2. modify copy in workspace
3. checkin


*Versions Terminology*
* Version ▶️ revision | variant
* Revision ▶️ a software object that was created by modyfying an existing one
* Variant ▶️ two software objects sharing an important property, differing in others

*Using Deltas to Reduce Version Space:* A delta is a difference between 2 revisions. 
- It can be computed in forward ▶️ or backward :arrow_backward: direction on checkin. 
- Used to regenerate one revision from another.

*Merging of Versions*
- line based produces too many false conflicts
- full semantic merging not practical
- structural (smart) merges

*Configuration Terminology*
- Release ▶️ a version that has been made available to user / client
- Configuration ▶️ combination of components into a system according to case-specific criteria
- Baseline ▶️ a static reference point for any configurable items in the project
*Note: does not imply that baseline is "perfect". It is only stating, in an example of software development, that the current version of the code is locked down so it can be verified and validated (tested)*

**3 Major Configuration Models**
1. Composition Model
```C
configuration = set of software objects 
--module oriented aspect
```
2. Change Set Model
```C
conf = bundle of changes
--dynamic aspect
```
3. Long Transaction Model
```C
conf = all changes are isolated into transactions
--collaborative aspect
```
*Configuration = selection of components from repository which together make up a release*

***Rule-Based Conf Building***
1. Baseline (default) ▶️ no versions, no selection needed
2. Developer ▶️ select all versions checked out by him, the newwest revision on main branch for others
3. Cautioud Developer ▶️ select last baseline (all versions checked in and out by him)
4. Reconfiguration ▶️ select according to variants by attribute (e.g. platform = Unix)
5. Time machine ▶️ ignore everything after a cutoff date
6. New Release ▶️ select acc. to the newest, stable versions that are associated with a given conf of change requests

*SVN(subversion) commands*
```bash
- svn import some_link myproject
- svn checkout somelink -d myproject
- svn status myfile.cc
- svn update myfile.cc
- svn diff myfile.cc
- svn commit myfile.cc
```

*make* => Controls generation of derivatives from their prerequisites
=> conf rule base: builtin, Makefile, makefile
=> rule format: 
```C
target: prerequisites
    how-to-generate
```
=> Macro (variable)
```bash
$@ Full name of current target
$? current dependencies out-of-date
$< source file of current dependency
```

***Multistep Generation*** ▶️ makefile can contain any nr of rules (adv: update only when needed)

<h3 style="color: purple">Software Testing</h3>
▶️ process of exercising a program with the specific intent of finding errors prior to delivery to the end user
▶️ performed by developer and independent tester

What users need <-----------------Acceptance Testing
:arrow_double_down: Requirements <----------------System testing
$\qquad$:arrow_double_down:Design<--------------------Integration testing
$\qquad\qquad$:arrow_double_down:Code <--------------Unit testing

**Unit Testing**
- Test unit = code that tests target
- Test case = test of an assertion or particular feature 
- Test driver = dummy environment for test class
- Test stub = dummy methods of classes used, but not available
- Good test cases = likely to produce an error

▶️ *Equivalence Class Testing Idea: build equivalence classes of test input situations, test one candidate per class*

▶️ *Integration testing = test interactions among units*

▶️ *Strategies: Big-bang, incremental (top-down, bottom-up, sandwich)*
```bash
Top-Down Integration:
-> top module is tested with stubs
-> stubs are replaced one at a time, "depth first"
-> as new modules are integrated, some subset of tests is re-run
```
```bash
Bottom-Up Integration:
-> deivers are replaced one at a time, "depth first"
-> worker modules are grouped into builds and integrated
```
```bash
Sandwich Testing:
-> Top modules are testes with stubs
-> Worker modules are grouped into builds and integrated
```
**System testing**
▶️ Determine whether system meets requirements = integrated hardware and software
▶️ Focus on use & interaction of sys functionalities
▶️ Should be carried out by a group independent of the code developers

**Acceptance Testing**
▶️ Goal to get approval from customer
▶️ Be sure the demo works
▶️ Customer may be tempted to demand more functionality when getting exposed to new system
▶️ Prepare with stakeholders well in advance

***Testing Methods***
- Static testing
    - collects info about a software without executing it
    - reviews, walkthroughs, formal verification, documentation testing
- Dynamic testing
    - collects info with executing the software
    - white-box vs black-box testing, memory leaks, coverage analysis, performance profiling
- Regression testing

*Static Analysis*
=> Control flow and data flow analysis
=> Examples of errors that can be found (unreachable statements, variables used before initialization, array bounds etc.)
=> Extensive tool support for deriving metrisc from src code

*Formal Verification*
=> Given a model of a program and a property, determine whether the model satisfies property, based on math
=> Ex: safety, liveness

**Black-Box = Spec-Based Testing**
▶️ No knowledge about code internals, relying only on interface spec
▶️ Limitations: specifications not usually available, many companies stilll have only code, no other doc

**White-Box(Glass-Box) Testing**
▶️ Check that all statements & conditions have been executed at least once
▶️ Look inside modules/classes
▶️ Limitations: cannot catch omission errors, cannot provide test oracles

***Coverage Analysis***
▶️ Measuring how much of the code has been exercised
```
- identify unexecuted code structures
- remove dead or unwanted code
- add more test cases?
```
▶️ Metrics inlude:
```
1. Entry points
2. Statements
3. Conditions (loops)
```

*Path Testing* 
▶️ cyclomatic complexity of flow graph:
```C
V(G) = nr of simple decisions + 1
( V(G) = number of enclosed areas + 1 )
```
▶️ derive independent paths and test cases to exercise these paths

*Equivalence classes*
▶️ build equivalence classes of test input situations, test one cadidate per class

*Terminology Cx*
```C++
C0 = every instruction
C1 = every branch (even if there is no else)
C2, C3 = every condition once true, once false
C4 = path coverage: every possible pasth taken (if/if ex.)
Rule of thumb: 95% C0, 70% C1
C2, C3 IMHO add no value, C4 often impossible
```
Levels according to severity of consequences:
• Level A: catastrophic ▶️ Modified cond. decision covg. + branch/decision + statement
• Level B: dangerous/severe ▶️ Branch/decision + statement
• Level C: significant ▶️ statement
• Level D: low impact
• Level E: no impact

**Memory Leaks**
▶️ memory gets allocated, but not released anymore
▶️ reduce performace due to excessive resource usage
▶️ may cause crashes
▶️ Note: Pointer errors form one of the biggest problem sources in C/C++ and similar languages

*Stacks and Heaps*
▶️ Stack: automatic management, stack pointer marks limit of valid data on stackcompiler generates code to edit stack, local variables, function return addresses
▶️ Heap: explicit allocation and deallocation using malloc() / free or new / delete, pointer targets

**Performance Profiler**
▶️ Code profiling = benchmarking execution to understand where time is being spent
```
▶ Technique:
• Profiler runs while application runs
• records frequency & time spent in each line of code
• Generates log file
```
**Regression Testing**
▶️ Run tests, compare output to same test on previous code version
▶️ Adv: easy automatic testing
▶️ Limitations: finds only deviations, cannot judje on error; can only find newly introduced deviations; only reasonable for fully automated tests

**Create Testable Software**
- Simplicity
- Decomposability (Modules can be testes independently)
- Controllability (Tests can be automated and reproduced)
- Observability (Queryable status, have class-internal checks & logging)
- Stability
- Operability
- Understanability

*Symptoms & Causes*
- *symptom* and *cause* may be geographically separated
- *symptom* may disappear when another problem is fixed
- *symptom* may be intermittent
- *cause* may be due to a combination of non-errors
- *cause* may be due to a system or compiler error
- *cause* may be due to assumptions that everyone believes

**Economics of Testing (graphs)**
▶️ Testing tends to intercept errors in order of their probability of occurrence
▶️ Verification is insensitive to the probability of occurrence of errors

**Objective test strategy should achieve “an acceptable level of confidence at an acceptable level of cost”**

<h4 style="color: darkgreen">The Maintenance Phase - Bug Tracking</h4>

**Bugs**
▶️ Bug = inexplicable defect
▶️ Software updates = new release to cure defects, respond to Requests for Enhancement (RFEs)
▶️ Update is either incremental ("patch") or full
```bash
Bug Anatomy
- Component: module where the bug occurred
- Status: short notes
- Keywords: e.g. test cases, help requested
- Target Milestone: estimated fix date or release version
* Dependency:
    -> Bugs this one depends on
    -> Bugs that depend on this one
    -> Bugzilla can display the dependecy graph
* Attachment:
    -> test cases, screen shots, editor logs, patch file
```

*Life cycle of a bug:*
- Bug log entry is created and assigned to developer with status NEW
- NEW bugs that are idle for a week trigger email reminders
- Reassigning a bug to someone else resets status to (NEW ->) Assigned
- Other fields updated during debugging process (with comments)
- Resolution => Fixed bugs are marked RESOLVED and receive a resolution:
    - FIXED: source updated and tested
    - INVALID: not a bug in the code
    - WONTFIX: “feature”, not a bug
    - DUPLICATE: already reported elsewhere; include reference
    - WORKSFORME: couldn’t reproduce
- Check => QA engineer checks resolved bugs
    - Verifies appropriate actions
    - Mark VERIFIED (okay)
    - Mark REOPENED (found issue)
- After product ships and is accepted by the customer…
    - Mark CLOSED (finally!)

*Bugzilla* ▶️ database for bugs, user can report bugs, developers can keep a to-do list, prioritize and track bug dependecies

**Trac** ▶️ an integrated tool for software project management

Bug reports should be:
▶️ Reproducible: provide relevant detail
▶️ Specific: isolate the cause if possible

<h4 style="color: seagreen">Documentation</h4>

**Types:**
- Internal documentation (comments in code, local level of detail)
```bash
*What should always be commented:*
1. Every file to say what it contains
2. Every function - what it takes and returns
3. Every variable apart from "obvious" ones
4. Every struct/typedef
```
- External programmer documentation (for other programmers working with your code, global level of detail)
```bash
Global structure:
Stage 1: overview & purpose
Stage 2: the mechanics
Stage 3: the gory details: globals
Stage 4: the gory details: locals
```
- User documentation (manual for users, global level of detail)
```bash
-> Sometimes it is written before your code is even ready to be tested
-> For highly structured and complex projects it is likely that you will have to adapt your
code to match the user manual
-> It has to be written from the point of view of the end users of your program
-> Many, many more considerations and guidelines not covered here…
```
*European Cooperation for Space Standardization overview*
- develop a coherent, single set of user-friendly standards for use in all European space activities
- publicly available, result of consultation with space agencies in Europe and industry, designed to secure acceptance by users
- requirement should address its need, rather than the means to fulfill it

*4 "Space" branches*
```bash
Engineering (E) | Project management (M) |
Product assurance (Q) | Space sustainability (U)
```
▶️ For each software “component”: Identifier, Type, Purpose, Function, Subordinates, Dependencies, Interfaces, Resources, References, Data

<h3 style="color: darkorange">Application Architectures</h3>

**Usage:**
- As a starting point for architectural design
- As a design checklist
- As a way of organizing the work of the dev team
- As a means of assessing components for reuse
- As a vocabulary for talking about application types

*Application types:*
- Data processing appl
```
Data driven applications that process data in batches without explicit user intervention during the
processing.
Ex: Billing, Payroll systems
```
- Transaction proc appl
```
Data-centred applications that process user requests and update information in a database.
Ex: E-commerce systems, Reservation sys
```
- Event proc systems
```
Applications where system actions depend on interpreting events from the system’s environment.
Ex: Word processors, real-time sys
```
- Language proc sys
```
Applications where the users’ intentions are specified in a formal language that is processed and
interpreted by the system.
Ex: compilers, command interpreters
```

<h4 style="color: salmon">Graphical User Interface</h4>

*Sequential Programs* (don’t work as well for graphical and for highly-interactive apps)
- Prompt user for input
- Program reads in a line of text
- Program runs for a while (user waits)
- Maybe some output
- Loop back to beginning

*3 concepts of modern GUI Systems:*
1. Event-driven programming
```C++
* All communication from user to computer is done via "events" (ex: "mouse button went down")
Events have:
* type
* mousse position or character key + modifiers
* ... + possible additional, application-dependent info

=> All events generated go to a single event queue
• provided by operating system
• ensures that events are handled in the order they occurred
• hides specifics of input from apps
```
2. Widgets
```C++
=> reusable interactive objects
Tasks:
* handle certain events
* update appearance
* generate some new events
* sends these events to interested listeners instead
```
3. Interactor Tree
```C++
=> decompose interactive objects into a tree
```
*MVC pattern as GUI paradigm:*
**Model** ▶️ Information the app is trying to manipulate
**View** ▶️ Implements a visual rep/display of the model
**Controller** ▶️ Receives all input events from the user, decides what they mean and what to do (commuincates with *View* and calls model methods)

*View/Controller Relationship* = pattern of behavior in response to user events (controller issues) is independent of visual geometry (view issues)

```C++
* Combining MVC into one class or using global variables will not scale
* Separation eases maintenance
```

<h4 style="color: coral">Web Service Foundations</h4>

* Information modelling ▶️ DOM
* Communication modelling ▶️ AJAX

▶️ GUI Interactor => DOM
▶️ HTML with CSS = encoding for DOM trees
▶️ "Custom Code" = js, DOM manipulation + AJAX

**Document Object Model** ▶️ tree representing browser window contents
▶️ Element (node) = object + attributes + text
▶️ Document = root node (<html>)
```html
Example:
Element: <body>, <a>
Attribute: href
Text: "My title"
```
***CSS*** = simple language for pre-setting of DOM attributes (settings for attributes)

**Asynchronous Javascript and XML** ▶️ web development technique for creating more interactive web applications
▶️ asynchronous: c/s communication independent from normal page loading
▶️  uses standardized components, supported by all major browsers: JavaScript, [ XML | JSON ], HTML, CSS

*JavaScript XMLHttpRequest object*
=> sends data, waits for response via event handler
=> replaces <FORM> and HTTP GET / POST

*Client DOM manipulated to dynamically display & interact*
=> inject response into any place of DOM tree
=> client-side scripting language: js etc.
```
Data format ex: XML, JSON, HTML, text, ...
Server agent ex: Servlet, script, ...
```

**JSON security concerns**
▶️ Js eval() - executes code received
▶️ Invitation to hack - embed rogue Js code(server-side atttack), intercept JSON data eval(client-side attack)
    => safe alternative: use parseJSON()
▶️ Cross-site request forgery (XSS attack) - malicious page can request and obtain JSON data belonging to another site

*XMLHttpRequest object part of std DOM*
*Code needs to detect at runtime: feature detection („sniffing“)*
*Frameworks provide abstraction layers*

**jQuery** ▶️ sample tool support

**AJAX Advantages**
- Reduced bandwidth usage
    - no complete reload/redraw
    - HTML generated locally
    - only actual data transferred
    - payload coming down much smaller in size
- Deferred loading
- Separation of data, format, style, and function

**Disadvantages**
- Browser integration (not in browser history, bookmarks)
- Search engine optimization
- Web analytics (tracking of accessing page vs portion of page vs click)
- Response time (effects from delays sometimes difficult to understand for users)
- Reliance on JS
    - large script files => delayed loading
    - IDE support emerging
    - users can disable JS
- Security (malicious code, XSS)

**Summary**
▶️ DOM = tree structure for Web content
▶️ HTML = contents & structure => DOM elements
▶️ CSS = styling & handling => DOM attributes
▶️ JavaScript = dynamics => functions on DOM
▶️ JSON = JavaScript subset => DOM data

<h4 style="color: seagreen">Web-Enabled
Information Systems</h4>

**Components of Data-Intensive Systems**
1. Presentation
    - primary interface to the user
    - needs adaptation to different display devices
    - HTML, Javascript, XSLT
2. Application ("bussiness") logic
    - implements complex actions, maintains state btw different steps of a workflow
    - accesses diff data management systems
    - CGI, ASP, PHP, Python, Servlets, Cookies
3. Data management
    - one or more standard database management systems
    - Tables, XML, Stored Procedures
- Single or Distributed system

*Web Content Management Systems Scheme:*
1. Hard-coded business logic
```C
HTML client <--HTTP--> HTML generator <---- database
=> Implementation <--business logic modelling <--Hypermedia modelling
```
2. Configured buisiness logic
```C
HTML client <--                       <--> database
               | --- code generator --|
XML client  <--                       <-- config repo <-- admin tool
```

**Query Mechanisms**
- one or more form entries
- qualitative / fuzzy search
- advanced search criteria, including joins
- drop-down lists generated from database contents
- tree-based & other representations using js

**Modelling Tool**
- modular design
- user-defines layout elements (down yo HTML/XML tags)

*Advantages of WCMS*
```
1. Low cost
2. Rapid prototyping & deployment for small installations
3. Plugin / Add-on extensibility
4. Personalisation, role-based access control, workflow control
5. Web-based administration & maintenance
6. Flexible target formats from one source
```
*Disadvantages*
```
1. Total cost of ownership (TCO)
    -> may require training for efficient use, dedicated hardware maintenance or licensing costs
    -> if web provided as a service, forces to its continuous updaye
2. Performance
    -> larger installations can incur performance issues due to under optimization (DBMS) or inadequate hardware capacity
```

**WebApp Attributes**
▶️ Network intensiveness
```
- Served and accessed over the network
- Diverse community of clients (browsers)
```
▶️ Concurrency
```
- Large nr of users may access at same time
- Patterns of usage vary greatly
```
▶️ Unpredictable load
```
- Nr of users may vary by orders of magnitude from day to day
```
▶️ Performance
```
- If user must wait too long may go elsewhere
- Server-side processing, client-side formatting and display...
```
▶️ Availability
```
- 100% avail. unreasonable
- Yet users often demand all the time access
```
▶️ Data driven
```
- Primary function of WebApps: use hypermedia to present text, graphics, audio/video content
- Document MS, CMS, WCMS
```
▶️ Content sensitive
```
- Up to date, comprehensive, customer-oriented
```
▶️ Aesthetics
```
- As critical as technical design
```
▶️ Immediacy
```
- Time to market a feq days/weeks
- Sophisticated web pages within few hours using modern tools
```
▶️ Continuous evolution
```
- Conventional software: evolves
- Web appl evolve also
```
▶️ Security
```
- Protect sensitive content + provide secure transmission
- HTTPS, SSL...
```

***=> Selenium: browser automation***
▶ Selenium automates browsers, it enables content verification
▶️ Selenium IDE: Firefox add-on for record-and-playback of interactions
- bug reproduction scripts
- scripts for automation-aided exploratory testing

▶️ Selenium WebDriver: language specific bindings to drive a browser
- browser-based regression automation
- distribute scripts across many environments

<h3 style="color: dodgerblue">User Interface Design</h3>

*Human factors in interface design:*
- Limited short-term memory
```
If more than ~7 items are presented, people can make mistakes
```
- People make mistakes
```
Inappropriate alarms and messages when systems go wrong can increase stress and hence the likelihood of more mistakes
```
- People are different
- People have diff interaction preferences

**Pressman's Golden Rules**
1. Place user in control
```
- define interaction modes clearly
- provide for flexible interaction
- allow user interaction to be interruptible and undoable, customized
- hide technical internals from casual user
- design for direct interaction 
```
2. Reduce user's memory load
```
- reduce demand on short-term mem
- establish meaningful defaults
- define shortcuts that are intuitive
- base vidual layout on a real world metaphor
- disclose info in a progressive fashion
```
3. Make interface consistent
```
- allow user to put current task into a meaningful context
- maintain consistency across a family of applications
- if past interactive models have created user expectations, do not change, unless necessary
```

**Analysis Techniques**
- Task Analysis
    - Model steps involved in completing a task
- Interviewing and questionnaires
    - Ask users about work they do
    - Use open-ended questions
    - Group interviews / focus groups discuss with each other what they do
- Ethnography
    - Observes user at work, questions them
    - Valuable to find intuitively done steps
    + to understand role of social & organisational influences

*UI Prototyping Techniques*
1. Paper prototyping (sketches of the interface + storyboard)
2. Script-driven pro. (scripts + screens)
3. Visual programming (language designed for rapid dev)
4. Internet-based prot. (web browser + associated scripts)

*UI design process involves:*
• user analysis
• system prototyping
• prototype evaluation