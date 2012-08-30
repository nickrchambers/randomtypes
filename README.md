<h1>The Nowl Programming Language</h1>
This is a simple programming language that aims to settle the debate between static and dynamic typing. Instead, it introduces the concept of random typing, where the type of a variable is changed (randomly) whenever it is accessed.
<br/>
The basic commands are:<br/>
<table>
<tr><td>show x;</td><td>shows a variable or number (currently shows everything as ints)</td></tr>
<tr><td>do x times ... </td><td>does ... x times</td></tr>
<tr><td>loop ... </td><td>does ... forever</td></tr>
<tr><td>stop; </td><td>stops a loop/do</td></tr>
<tr><td>if(condition) consequent</td><td>if condition is true, execute consequent</td></tr>
<tr><td>fun name(params) ...</td><td>defines a function</td></tr>
<tr><td>return x;</td><td>returns a value from a function</td></tr>
<tr><td>x::</td><td>gives variable x's type - either ::int, ::bool or ::char</td></tr>
<tr><td>x+y, x-y, x/y, xy</td><td>Usual integer arithmetical operators</td></tr>
<tr><td>x==y, x!=y, x&gt;y, x&lt;y, x&gt;=y, x&lt;=y, !x</td><td>Usual logical operators</td></tr>
<tr><td>x=y</td><td>Assigns y's value to x</td></tr></table>
<br/>
The problem with both statically and dynamically typed languages is that they are entirely arbitrary - does anyone <i>really</i> have any good reasons for picking one way or the other? Randomly typed languages fix this with a powerful new programming paradigm.<br/>

However, with great power comes great responsibility. It is up to the programmer to check that variables are of the type required when accessed. The type of a variable may change when any operation that accesses or modifies its value executes. Thus, if one wishes to use variable a as an integer, the following code could be used:<br/>
<code>loop {<br/>
      &nbsp;&nbsp;&nbsp;&nbsp; t = a; <br/>
      &nbsp;&nbsp;&nbsp;&nbsp;  if(a:: == ::int) stop;<br/>
        }
</code>
<br/>
It is clearly important that this is done before variables are set as well as  read.<br/><br/>
This powerful method allows the user to practically forget about the fact that typing is entirely random, and concentrate on the code that matters.<br/><br/>

<h3>Language points</h3>
Variables can be used without being declared - they are automatically initialised to the default value (of their randomly chosen type). In a nod to Python, there is little variable scoping. Variables are local to functions, but blocks within functions are for control flow, not petty matters like variable scoping.
<br/>
Nowl's key innovation is dispensing with language-implemented type-checking. This is now left to the programmer, where it should be.<br/>

<h3>Naming</h3>
The name Nowl was, fittingly, chosen by using a random Markov model string generator. It'll do. <br/>
<h3>Implementation</h3>
Nowl is implemented using Flex and Bison, which should be available in most places. There are probably many errors in this hurried implementation - these are likely due to the difficulties of programming under the constraints of current systems' archaic typing rules.<br/>

<h3>Running programs</h3>
Programs can be run by executing ./lang &lt;src.nwl, if the program is in src.nwl. There are a few example programs in the repo.

<h3>Coding style</h3>
When multiple variables of certain types are needed, it seems tempting to use the above device separately for each variable. This is considered poor style as it adds to code bloat and unmaintainability. Instead, it is preferred to try to fix all variables' types at once. The difference is shown in fibonnaci.nwl and fibrecursive.nwl. fibrecursive.nwl also uses recursion, but the drastic difference in code size comes mainly from the use of good Nowl style.
