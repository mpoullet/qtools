/*! @page qspy QSPY Host Application

@tableofcontents

@section qspy_about About QSPY
<p>As described in the @ref qspy_system "previous section", **QSPY** is the host-resident component in the Q-SPY software tracing system. QSPY is a plain console application without a GUI, because its main purpose is to provide the parsing of the @ref qspy_protocol "Q-SPY Data Protocol" and displaying the data in a simple @ref qspy_text "human-readable format". QSPY can also export the data in various other formats, such as
format suitable for @ref qspy_matlab "MATLAB/GNU-Octave", and format suitable for generating message sequence diagrams with @ref qspy_mscgen "MscGen". Additionally, QSPY can also save the symbolic information about the Target objects in form of @ref qspy_dict "QSPY dictionaries".
</p>

Starting with version 5.5.0, QSPY can serve a "Back-End" for attaching various **GUI-based** or head-less "Front-Ends" (such as the @ref qspyview "QSpyView Front-End").

@note
The fact that QSPY is a simple console application allows it to be "platform-neutral". QSPY is written in portable C with ports to Windows and Linux provided. QSPY is also designed to be adaptable to various target-host communication links. Out of the box, the QSPY host application supports serial (RS232), TCP/IP, and file communication links. Adding other communication links is straightforward, because the data link is accessed only through a generic Platform Abstraction Layer (PAL).


-------------------------------------------------------------------------------
@section qspy_command QSPY Command-Line Parameters
<p>The QSPY application accepts several command-line parameters to configure the data link to the Target, backwards-compatibly with previous versions, and target dependencies, such as pointer sizes, signal sizes, etc. This means that the single QSPY host application can process data from any Target running the QS component. QSPY has been tested with wide range of 8-, 16-, 32-, and 64-bit CPUs.
</p>

The general form of invoking QSPY is as follows:

@verbatim
qspy [options]
@endverbatim

where `options` are described in the following table:

@attention
You should **not** insert spaces between an option and the argument:@n
`qspy -t 6602  <-- INCORRECT!!` @n
`qspy -t6602   <-- CORRECT`


<TABLE SUMMARY="QSPY options" cellSpacing=4 cellPadding=1 border=0
ALIGN="center" VALIGN="middle">
  <TR bgColor="#c8cedc">
    <TD><B>&nbsp;Option</B></TD>
    <TD><B>&nbsp;Example</B></TD>
    <TD><B>&nbsp;Default@n (key)</B></TD>
    <TD><B>&nbsp;Must match QP macro@n (QP port header file)</B></TD>
    <TD><B>&nbsp;Comments</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>-h</TD>
    <TD>-h</TD>
    <TD></TD>
    <TD></TD>
    <TD>Help. Prints the summary of options</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>-q</TD>
    <TD>-q</TD>
    <TD>(key-q)</TD>
    <TD></TD>
    <TD>Quiet mode (no stdout output)</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>-u[port]</TD>
    <TD>-u</TD>
    <TD>7701</TD>
    <TD></TD>
    <TD>UDP socket for "Front-Ends"</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>-v</TD>
    <TD>-v 5.5</TD>
    <TD>5.0</TD>
    <TD></TD>
    <TD>Compatibility with QS version</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>-o</TD>
    <TD>-o</TD>
    <TD>(key-o)</TD>
    <TD></TD>
    <TD>Produce output to the specified file</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>-s</TD>
    <TD>-s</TD>
    <TD>(key-s)</TD>
    <TD></TD>
    <TD>Save the binary input to a file. Not compatible with -f
    </TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>-m</TD>
    <TD>-m</TD>
    <TD>(key-m)</TD>
    <TD></TD>
    <TD>Produce @ref qspy_matlab "MATLAB/GNU-Octave output" to a file</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>-g</TD>
    <TD>-g</TD>
    <TD>(key-g)</TD>
    <TD></TD>
    <TD>Produce @ref qspy_mscgen "MscGen output" to a file</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>-c&lt;port&gt;</TD>
    <TD>-cCOM2</TD>
    <TD>COM1</TD>
    <TD></TD>
    <TD>COM port selection. Not compatible with -t, -p, -f</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>-b&lt;baud&gt;</TD>
    <TD>-b38400</TD>
    <TD>115200</TD>
    <TD></TD>
    <TD>Baud rate selection. Not compatible with -t, -p, -f</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>-t&lt;port&gt;</TD>
    <TD>-t</TD>
    <TD>6601</TD>
    <TD></TD>
    <TD>TCP/IP input selection. Not compatible with -c, -b, -f</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>-f&lt;file&gt;</TD>
    <TD>-fqs.spy</TD>
    <TD></TD>
    <TD></TD>
    <TD>File input selection. Not compatible with -c, -b, -t, -p</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>-d&lt;file&gt;</TD>
    <TD>-dqspy150831_144229.dic</TD>
    <TD></TD>
    <TD></TD>
    <TD>Read dictionaries from a file.</TD>
  </TR>

  <TR bgColor="#f0f0c0">
    <TD colspan="5"><strong>Options for configuring Target object sizes:</strong>@n
Starting with QS/QSPY 5.5.0, the Target can **report** it's configuration to QSPY, which means that you don't need to provide any upper-case options (such as: `-T`, `-O`, `-F`, etc.).
    </TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>-T&lt;size&gt;</TD>
    <TD>-T2</TD>
    <TD>4</TD>
    <TD>@c QS_TIME_SIZE @n (qs_port.h)</TD>
    <TD>Time stamp size in bytes. Valid values: 1, 2, 4</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>-O&lt;size&gt;</TD>
    <TD>-O2</TD>
    <TD>4</TD>
    <TD>@c QS_OBJ_PTR_SIZE @n (qs_port.h)</TD>
    <TD>Object pointer size in bytes. Valid values: 1, 2, 4, 8</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>-F&lt;size&gt;</TD>
    <TD>-F2</TD>
    <TD>4</TD>
    <TD>@c QS_FUN_PTR_SIZE @n (qs_port.h)</TD>
    <TD>Function pointer size in bytes. Valid values: 1, 2, 4, 8</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>-S&lt;size&gt;</TD>
    <TD>-S1</TD>
    <TD>2</TD>
    <TD>@c Q_SIGNAL_SIZE @n (qep_port.h)</TD>
    <TD>Signal size in bytes. Valid values: 1, 2, 4</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>-E&lt;size&gt;</TD>
    <TD>-E1</TD>
    <TD>2</TD>
    <TD>@c QF_EVENT_SIZ_SIZE @n (qf_port.h)</TD>
    <TD>Event-size size in bytes (i.e., the size of variables that hold
        event size). Valid values: 1, 2, 4</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>-Q&lt;size&gt;</TD>
    <TD>-Q2</TD>
    <TD>1</TD>
    <TD>@c QF_EQUEUE_CTR_SIZE @n (qf_port.h)</TD>
    <TD>Queue counter size in bytes. Valid values 1, 2, 4</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>-P&lt;size&gt;</TD>
    <TD>-P4</TD>
    <TD>2</TD>
    <TD>@c QF_MPOOL_CTR_SIZE @n (qf_port.h)</TD>
    <TD>Pool counter size in bytes. Valid values: 1, 2, 4</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>-B&lt;size&gt;</TD>
    <TD>-B1</TD>
    <TD>2</TD>
    <TD>@c QF_MPOOL_SIZ_SIZE @n (qf_port.h)</TD>
    <TD>Block size size in bytes. (i.e., the size of variables that hold
        memory block size). Valid values 1, 2, 4</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>-C&lt;size&gt;</TD>
    <TD>-C4</TD>
    <TD>2</TD>
    <TD>@c QF_TIMEEVT_CTR_SIZE @n (qf_port.h)</TD>
    <TD>Time event counter size. Valid values: 1, 2, 4</TD>
  </TR>
</TABLE>


Your main concern when invoking QSPY is to match exactly the target system you
are using. The fourth column of the table above lists the configuration macros
used by the target system as well as the platform-specific QP header files
where those macros are defined. You need to use the corresponding QSPY
command-line option only when the QP macro differs from the default. The
default values assumed by QSPY are consistent with the defaults used in QP.

@note
When you do not match the QSPY host application with the QS target
component, the QSPY application will be unable to parse correctly the
mismatched trace records and will start generating the following errors:

@verbatim
********** 028: Error xx bytes unparsed
********** 014: Error -yy bytes unparsed
@endverbatim

The number in front of the error indicates the <a href="qs__copy_8h.html#acdb495c1e5524b5d95aaff82c47f6db5"><strong>Record ID</strong></a> of the trace record
that could not be parsed.


-------------------------------------------------------------------------------
@section qspy_keyboard QSPY Keyboard Commands
Starting from version 5.5.0, QSPY accepts keyboard input. The following table shows the currently supported key-strokes:


Key | Action
----|---------
&lt;Esc&gt; | Exit QSPY
h           | display keyboard help and QSPY status
c           | clear the screen
q           | toggle quite mode (no Target output to the screen</TD>
r           | send RESET command to the Target
i           | send the INFO request to the Target (see also @ref qspy_dict)
t           | send TIKC[0] command to the Target
u           | send TICK[1] command to the Target
d           | save @ref qspy_dict "Q-SPY Dictionaries" to a file
o           | toggle @ref qspy_text "QSPY Human-Readable Output" to a file (open/close)
s/b         | toggle binary file output (open/close)
m           | mtoggle @ref qspy_matlab "MATLAB Output" to a file (open/close)
g           | toggle @ref qspy_mscgen "MscGen Output" to a file (open/close)


@note
QSPY can send many more sophisticated commands to the Target by means of the @ref qspyview "Front-End extension mechanism".


-------------------------------------------------------------------------------
@section qspy_saving Saving Files from QSPY

QSPY can save the tracing data from the Target in various formats into files. QSPY assigns file names **automatically**. Also, QSPY can open/close various files multiple times in a single session, so it is no longer necessary to exit QSPY and launch it again with different command-line parameters to save data to a different file.

@attention
QSPY saves all files into the <strong>current directory</strong> from which `qspy` has been launched.

QSPY uses a very simple naming convention to assign file names. All names start with `qspy<time-stamp>`, where the  time-stamp format is: `YYMMDD_hhmmss`, where `YY` is 2-digit year, `MM` is a 2-digit month, `DD` is a 2-digit day of the month, `hh` is a 2-digit hour, `mm` is a 2-digit minute, and `ss` is a 2-digit second. The time-stamp is accurate to a one second, so its virtually impossible to have name conflicts for files generated on the same machine. The various types of files are distinguished by the following extensions:

Extension |  Example |  Comment
----------|----------|-----------
`.txt` | `qspy150914_132234.txt` | @subpage qspy_text "text (screen) output"
`.dic` | `qspy150901_101203.dic` | @subpage qspy_dict "dictionary output"
`.qs`  | `qspy150914_132234.qs`  | raw binary output (@ref qspy_protocol "Q-SPY protocol") 
`.mat` | `qspy150914_132234.mat` | @subpage qspy_matlab "MATLAB output"
`.msc` | `qspy150914_132234.msg` | @subpage qspy_mscgen "MscGen output"

@note
All files except the dictionary output are time-stamped with the <strong>local</strong> time of the Host. The **dictionary** output is time-stamped with the build-time of the Target image.

@next{qspy_text}
*/
/*###########################################################################*/
/**
@page qspy_text QSPY Screen Output

@tableofcontents

<p>QSPY provides a simple consolidated, human-readable textual output to the screen. The readability of this output depends strongly on the availability of the <em>symbolic information</em> about the various objects in the Target code, called @ref qspy_dict "dictionaries". If the "dictionaries" are not available, QSPY can output only the hexadecimal values of various object addresses and event signals. However, if QSPY has acquired the "dictionaries" from the Target, or has @ref qspy_dict_read "read them from a file", it can apply the symbolic information to output the provided identifiers for objects, signals, and states.
</p>


-------------------------------------------------------------------------------
@section qspy_text_exa Screen Output Example
For example, the following listing shows the QSPY text output when the "dictionaries" **are** available:

@verbatim
QSPY host application 5.5.0
Copyright (c) Quantum Leaps, state-machine.com
Time Stamp: 150914_131608
-v550
-T4
-O4
-F4
-S2
-E2
-Q1
-P2
-B2
-C2

********** TARGET: QP-Ver: 550, build tstamp:150831_144229
           Obj-Dic: 0000000000004018->QS_RX
           Obj-Dic: 0000000000003B18->l_SysTick_Handler
           Obj-Dic: 0000000000003B19->l_GPIOPortA_IRQHandler
           Usr-Dic: 00000046        ->PHILO_STAT
. . . . . .
           Fun-Dic: 0000000000000A79->Philo_initial
           Fun-Dic: 0000000000000D01->Philo_thinking
           Fun-Dic: 0000000000000C99->Philo_hungry
           Fun-Dic: 0000000000000C45->Philo_eating
           Sig-Dic: 0000000A,Obj=0000000020000D60->HUNGRY_SIG
           Sig-Dic: 0000000B,Obj=0000000020000D60->TIMEOUT_SIG
. . . . . .
0000500000 PHILO_STAT: 0 thinking
0000500000 PHILO_STAT: 1 thinking
0000500000 PHILO_STAT: 2 thinking
0000500000 PHILO_STAT: 3 thinking
0000500000 PHILO_STAT: 4 thinking
           INIT : Obj=l_table Source=NULL Target=Table_serving
           ENTRY: Obj=l_table State=Table_serving
0000500000 ==>Init: Obj=l_table New=Table_serving
0001000995 Disp==>: Obj=l_table Sig=SERVE_SIG Active=Table_serving
0001001751 Ignored: Obj=l_table Sig=SERVE_SIG Active=Table_serving
0025500773 Disp==>: Obj=l_philo[4] Sig=TIMEOUT_SIG Active=Philo_thinking
           ENTRY: Obj=l_philo[4] State=Philo_hungry
0025502307 ==>Tran: Obj=l_philo[4] Sig=TIMEOUT_SIG Source=Philo_thinking New=Philo_hungry
0025503277 Disp==>: Obj=l_table Sig=HUNGRY_SIG Active=Table_serving
0025503983 PHILO_STAT: 4 hungry
0025505703 PHILO_STAT: 4 eating
0025506279 Intern : Obj=l_table Sig=HUNGRY_SIG Source=Table_serving
0025507211 Disp==>: Obj=l_philo[4] Sig=EAT_SIG Active=Philo_hungry
           ENTRY: Obj=l_philo[4] State=Philo_eating
0025508581 ==>Tran: Obj=l_philo[4] Sig=EAT_SIG Source=Philo_hungry New=Philo_eating
0025509563 Disp==>: Obj=l_philo[3] Sig=EAT_SIG Active=Philo_thinking
0025510253 Intern : Obj=l_philo[3] Sig=EAT_SIG Source=Philo_thinking
. . . . . .
@endverbatim

The QS trace log shown in the listing above contains quite detailed information, because most QS records are enabled (are not blocked in the @ref "QS filters"). The following bullet items highlight the most interesting parts of the trace and illustrate how you can interpret the trace data:

- The QS output starts with the QSPY application version number, the date and time of the run (Time Stamp), and all the options explicitly provided to the QSPY host application.

- The first trace records in the log are typically @ref qspy_dict "dictionary trace records" that provide a mapping between addresses of various objects in memory and their symbolic names.

- After the dictionaries, you see the active object initialization. For example, the `INIT` record indicates that the top-most initial transition in the active object `l_table` has been taken. After this, the `ENTRY` record informs you that the state `Table_serving` has been entered, and finally the record `==>Init` tells you that the top-most initial transition sequence has completed. This trace record has a high-resolution **time-stamp** (the first 8-digit number) generated by the Target. The time units used by this time-stamp depend on the specific hardware timer used in the Target, but typically it is sub-microsecond.

- After this you see that at the time-stamp `0001000995` an event was dispatched (`Disp==>` record) to `l_table`, but it was subsequently `Ignored`, while `l_table` was in the state `Table_serving`.


-------------------------------------------------------------------------------
@section qspy_text_table Standard Trace Records
The following table summarizes the text output format used for all standard QS trace records (see ::•QSpyRecords).

<TABLE SUMMARY="QEP Records" cellSpacing=4 cellPadding=1 border=0 width="95%">

  <TR bgColor="#f0f0c0">
      <TD colspan="4"><strong>QEP Trace Records</strong></TD>
  </TR>  

  <TR bgColor="#c8cedc">
    <TD><B>Rec.@n Num.</B></TD>
    <TD><B>Rec.@n Enum.</B></TD>
    <TD><B>QSPY@n Abbrev.@n</B></TD>
    <TD><B>Comment</B></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>1</TD>
    <TD>#QS_QEP_STATE_ENTRY</TD>
    <TD>Q_ENTRY</TD>
    <TD>a state was entered</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>2</TD>
    <TD>#QS_QEP_STATE_EXIT</TD>
    <TD>Q_EXIT</TD>
    <TD>a state was exited</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>3</TD>
    <TD>#QS_QEP_STATE_INIT</TD>
    <TD>Q_INIT</TD>
    <TD>an intial transition was taken in a state</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>4</TD>
    <TD>#QS_QEP_INIT_TRAN</TD>
    <TD>==>Init</TD>
    <TD>the top-most initial transition was taken</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>5</TD>
    <TD>#QS_QEP_INTERN_TRAN</TD>
    <TD>Intern</TD>
    <TD>an internal transition was taken</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>6</TD>
    <TD>#QS_QEP_TRAN</TD>
    <TD>==>Tran</TD>
    <TD>a regular transition was taken</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>7</TD>
    <TD>#QS_QEP_IGNORED</TD>
    <TD>Ignored</TD>
    <TD>an event was ignored (silently discarded)</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>8</TD>
    <TD>#QS_QEP_DISPATCH</TD>
    <TD>Disp==></TD>
    <TD>an event was dispatched (begin of RTC step)</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>9</TD>
    <TD>#QS_QEP_UNHANDLED</TD>
    <TD>==>UnHd</TD>
    <TD>a guard prevented handling of an event</TD>
  </TR>

  <TR bgColor="#f0f0c0">
      <TD colspan="4"><strong>QF Trace Records</strong></TD>
  </TR>  

  <TR bgColor="#c8cedc">
    <TD><B>Rec.@n Num.</B></TD>
    <TD><B>Rec.@n Enum.</B></TD>
    <TD><B>QSPY@n Abbrev.@n</B></TD>
    <TD><B>Comment</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>10</TD>
    <TD>#QS_QF_ACTIVE_ADD</TD>
    <TD>ADD</TD>
    <TD>an AO has been added to QF (started)</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>11</TD>
    <TD>#QS_QF_ACTIVE_REMOVE</TD>
    <TD>REM</TD>
    <TD>an AO has been removed from QF (stopped)</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>12</TD>
    <TD>#QS_QF_ACTIVE_SUBSCRIBE</TD>
    <TD>SUB</TD>
    <TD>an AO subscribed to an event</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>13</TD>
    <TD>#QS_QF_ACTIVE_UNSUBSCRIBE</TD>
    <TD>USUB</TD>
    <TD>an AO unsubscribed to an event</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>14</TD>
    <TD>#QS_QF_ACTIVE_POST_FIFO</TD>
    <TD>AO.FIFO</TD>
    <TD>an event was posted (FIFO) directly to AO</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>15</TD>
    <TD>#QS_QF_ACTIVE_POST_LIFO</TD>
    <TD>AO.LIFO</TD>
    <TD>an event was posted (LIFO) directly to AO</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>16</TD>
    <TD>#QS_QF_ACTIVE_GET</TD>
    <TD>AO.GET</TD>
    <TD>AO got an event and its queue is still not empty</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>17</TD>
    <TD>#QS_QF_ACTIVE_GET_LAST</TD>
    <TD>AO.GETL</TD>
    <TD>AO got an event and its queue is empty</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>18</TD>
    <TD>#QS_QF_EQUEUE_INIT</TD>
    <TD>EQ.INIT</TD>
    <TD>an event queue was initialized</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>19</TD>
    <TD>#QS_QF_EQUEUE_POST_FIFO</TD>
    <TD>EQ.FIFO</TD>
    <TD>an event was posted (FIFO) to a raw queue</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>20</TD>
    <TD>#QS_QF_EQUEUE_POST_LIFO</TD>
    <TD>EQ.LIFO</TD>
    <TD>an event was posted (LIFO) to a raw queue</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>21</TD>
    <TD>#QS_QF_EQUEUE_GET</TD>
    <TD>EQ.GET</TD>
    <TD>get an event and queue still not empty</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>22</TD>
    <TD>#QS_QF_EQUEUE_GET_LAST</TD>
    <TD>EQ.GETL</TD>
    <TD>get the last event from the queue</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>23</TD>
    <TD>#QS_QF_MPOOL_INIT</TD>
    <TD>MP.INIT</TD>
    <TD>a memory pool was initialized</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>24</TD>
    <TD>#QS_QF_MPOOL_GET</TD>
    <TD>MP.GET</TD>
    <TD>a memory block was removed from a memory pool</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>25</TD>
    <TD>#QS_QF_MPOOL_PUT</TD>
    <TD>MP.PUT</TD>
    <TD>a memory block was returned to a memory pool</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>26</TD>
    <TD>#QS_QF_PUBLISH</TD>
    <TD>PUBLISH</TD>
    <TD>an event was published</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>27</TD>
    <TD>RESERVED</TD>
    <TD></TD>
    <TD></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>28</TD>
    <TD>#QS_QF_NEW</TD>
    <TD>NEW</TD>
    <TD>new event creation</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>29</TD>
    <TD>#QS_QF_GC_ATTEMPT</TD>
    <TD>GC-ATT</TD>
    <TD>garbage collection attempt</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>30</TD>
    <TD>#QS_QF_GC</TD>
    <TD>GC</TD>
    <TD>garbage collection performed</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>31</TD>
    <TD>#QS_QF_TICK</TD>
    <TD>TICK</TD>
    <TD>QF_tick() was called</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>32</TD>
    <TD>#QS_QF_TIMEEVT_ARM</TD>
    <TD>TE.ARM</TD>
    <TD>a time event was armed</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>33</TD>
    <TD>#QS_QF_TIMEEVT_AUTO_DISARM</TD>
    <TD>TE.ADRM</TD>
    <TD>a time event expired and was disarmed</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>34</TD>
    <TD>#QS_QF_TIMEEVT_DISARM_ATTEMPT</TD>
    <TD>TE.DATT</TD>
    <TD>attempt to disarmed a disarmed tevent</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>35</TD>
    <TD>#QS_QF_TIMEEVT_DISARM</TD>
    <TD>TE.DARM</TD>
    <TD>true disarming of an armed time event</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>36</TD>
    <TD>#QS_QF_TIMEEVT_REARM</TD>
    <TD>TE.RARM</TD>
    <TD>rearming of a time event</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>37</TD>
    <TD>#QS_QF_TIMEEVT_POST</TD>
    <TD>TE.POST</TD>
    <TD>a time event posted itself directly to an AO</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>38</TD>
    <TD>#QS_QF_TIMEEVT_CTR</TD>
    <TD>TE.CTR</TD>
    <TD>a time event counter was requested </TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>39</TD>
    <TD>#QS_QF_INT_DISABLE</TD>
    <TD>QF_intL</TD>
    <TD>interrupts were disabled</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>40</TD>
    <TD>#QS_QF_INT_ENABLE</TD>
    <TD>QF_intU</TD>
    <TD>interrupts were enabled</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>42</TD>
    <TD>#QS_QF_ISR_ENTRY</TD>
    <TD>QF_isrE</TD>
    <TD>an ISR was entered</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>43</TD>
    <TD>#QS_QF_ISR_EXIT</TD>
    <TD>QF_isrX</TD>
    <TD>an ISR was exited</TD>
  </TR>
  
  <TR bgColor="#f0f0c0">
      <TD colspan="4"><strong>QK/QV Trace Records</strong>      </TD>
  </TR>  

  <TR bgColor="#c8cedc">
    <TD><B>Rec.@n Num.</B></TD>
    <TD><B>Rec.@n Enum.</B></TD>
    <TD><B>QSPY@n Abbrev.@n</B></TD>
    <TD><B>Comment</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>50</TD>
    <TD>#QS_QK_MUTEX_LOCK</TD>
    <TD>QK_muxL</TD>
    <TD>the QK mutex was locked</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>51</TD>
    <TD>#QS_QK_MUTEX_UNLOCK</TD>
    <TD>QK_muxU</TD>
    <TD>the QK mutex was unlocked</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>52</TD>
    <TD>#QS_QVK_SCHEDULE</TD>
    <TD>QVK_sche</TD>
    <TD>the QV/QK scheduled a new task to execute</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>53</TD>
    <TD>#QS_QVK_IDLE</TD>
    <TD>QVK_idle</TD>
    <TD>QK/QV became idle</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>54</TD>
    <TD>#QS_QK_RESUME</TD>
    <TD>QK_res</TD>
    <TD>QK resumed previous task (not idle)</TD>
  </TR>

  <TR bgColor="#f0f0c0">
      <TD colspan="4"><strong>Additional QEP Trace Records</strong></TD>
  </TR>  

  <TR bgColor="#c0c0c0">
    <TD>55</TD>
    <TD>#QS_QEP_TRAN_HIST</TD>
    <TD>QS.HIST</TD>
    <TD>a transition to history was taken</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>56</TD>
    <TD>#QS_QEP_TRAN_EP</TD>
    <TD>QS.EP</TD>
    <TD>a transition to entry point into a submachine</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>57</TD>
    <TD>#QS_QEP_TRAN_XP</TD>
    <TD>QS.XP</TD>
    <TD>a transition to exit point into a submachine</TD>
  </TR>

  <TR bgColor="#f07070">
      <TD colspan="4"><strong>Miscellaneous Trace Records@n
      NOT MASKABLE WITH THE GLOBAL FILTER!
      </strong>
      </TD>
  </TR>  

  <TR bgColor="#c8cedc">
    <TD><B>Rec.@n Num.</B></TD>
    <TD><B>Rec.@n Enum.</B></TD>
    <TD><B>QSPY@n Abbrev.</B></TD>
    <TD><B>Comment</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>60</TD>
    <TD>#QS_SIG_DICTIONARY</TD>
    <TD>Sig Dic</TD>
    <TD>signal dictionary entry</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>61</TD>
    <TD>#QS_OBJ_DICTIONARY</TD>
    <TD>Obj Dic</TD>
    <TD>object dictionary entry</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>62</TD>
    <TD>#QS_FUN_DICTIONARY</TD>
    <TD>Fun Dic</TD>
    <TD>function dictionary entry</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>63</TD>
    <TD>#QS_USR_DICTIONARY</TD>
    <TD>Usr Dic</TD>
    <TD>User record dictionary entry</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>64</TD>
    <TD>#QS_TARGET_INFO</TD>
    <TD>Info</TD>
    <TD>reports the Target information</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>65</TD>
    <TD>RESERVED</TD>
    <TD></TD>
    <TD></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>66</TD>
    <TD>#QS_RX_STATUS</TD>
    <TD></TD>
    <TD>reports QS data receive status</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>66</TD>
    <TD>#QS_TEST_STATUS</TD>
    <TD></TD>
    <TD>reports test status</TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>66</TD>
    <TD>#QS_PEEK_DATA</TD>
    <TD></TD>
    <TD>reports the data from the PEEK query</TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>67</TD>
    <TD>#QS_ASSERT_FAIL</TD>
    <TD>!ASSERT</TD>
    <TD>Assertion fired</TD>
  </TR>

  <TR bgColor="#f0f0c0">
      <TD colspan="4"><strong>User (Application Specific) Records</strong></TD>
  </TR>  

  <TR bgColor="#f0f0f0">
    <TD>70</TD>
    <TD>#QS_USER</TD>
    <TD>UserXXX</TD>
    <TD>the first record available for user QS records</TD>
  </TR>
</TABLE>

@next{qspy_dict}
*/
/*###########################################################################*/
/**
@page qspy_dict QSPY Dictionaries

@tableofcontents

@section qspy_dict_about About QSPY Dictionaries
By the time you compile and load your application image to the Target, the symbolic names of various objects, function names, and event signal names are stripped from the code. Therefore, if you want to have the symbolic information available to the QSPY host-resident component, you need to supply it somehow to the software tracing system.

The QS Target-resident component provides special **dictionary trace records** designed expressly for providing the symbolic information about the target code in the trace itself. These "dictionary records" are very much like the symbolic information embedded in the object files for the traditional single-step debugger. QS can supply four types of dictionary trace records: object dictionary, function dictionary,  signal dictionary, and user dictionary.

The dictionary trace records are not absolutely required to generate the human-readable output, in the same way as the symbolic information in the object files is not absolutely required to debug code. However, in both cases, the availability of the symbolic information greatly improves the productivity in working with the software trace or the debugger. For example, the following listing shows an example of the QSPY text output when the "dictionaries" are **not** available:

@verbatim
********** Data discontinuity: seq=1 -> seq=73
0148066147 Disp==>: Obj=20000E14 Sig=0000000B,Obj=20000E14 Active=00000D01
           ENTRY: Obj=20000E14 State=00000C99
0148067681 ==>Tran: Obj=20000E14 Sig=0000000B,Obj=20000E14 Source=00000D01 New=00000C99
0148068651 Disp==>: Obj=20000E90 Sig=0000000A,Obj=20000E90 Active=00001145
0148069357 User70: 3 hungry
0148069955 Intern : Obj=20000E90 Sig=0000000A,Obj=20000E90 Source=00001145
0181066185 Disp==>: Obj=20000D60 Sig=0000000B,Obj=20000D60 Active=00000D01
           ENTRY: Obj=20000D60 State=00000C99
0181067719 ==>Tran: Obj=20000D60 Sig=0000000B,Obj=20000D60 Source=00000D01 New=00000C99
0181068689 Disp==>: Obj=20000E90 Sig=0000000A,Obj=20000E90 Active=00001145
0181069395 User70: 0 hungry
0181069999 Intern : Obj=20000E90 Sig=0000000A,Obj=20000E90 Source=00001145
0185066099 Disp==>: Obj=20000E50 Sig=0000000B,Obj=20000E50 Active=00000C45
           EXIT : Obj=20000E50 State=00000C45
           ENTRY: Obj=20000E50 State=00000D01
0185068413 ==>Tran: Obj=20000E50 Sig=0000000B,Obj=20000E50 Source=00000C45 New=00000D01
. . . . . .
@endverbatim

And here is the exact same trace data when the "dictionaries" **are** available:

@verbatim
********** Data discontinuity: seq=1 -> seq=73
0148066147 Disp==>: Obj=l_philo[3] Sig=TIMEOUT_SIG Active=Philo_thinking
           ENTRY: Obj=l_philo[3] State=Philo_hungry
0148067681 ==>Tran: Obj=l_philo[3] Sig=TIMEOUT_SIG Source=Philo_thinking New=Philo_hungry
0148068651 Disp==>: Obj=l_table Sig=HUNGRY_SIG Active=Table_serving
0148069357 PHILO_STAT: 3 hungry
0148069955 Intern : Obj=l_table Sig=HUNGRY_SIG Source=Table_serving
0181066185 Disp==>: Obj=l_philo[0] Sig=TIMEOUT_SIG Active=Philo_thinking
           ENTRY: Obj=l_philo[0] State=Philo_hungry
0181067719 ==>Tran: Obj=l_philo[0] Sig=TIMEOUT_SIG Source=Philo_thinking New=Philo_hungry
0181068689 Disp==>: Obj=l_table Sig=HUNGRY_SIG Active=Table_serving
0181069395 PHILO_STAT: 0 hungry
0181069999 Intern : Obj=l_table Sig=HUNGRY_SIG Source=Table_serving
0185066099 Disp==>: Obj=l_philo[4] Sig=TIMEOUT_SIG Active=Philo_eating
           EXIT : Obj=l_philo[4] State=Philo_eating
           ENTRY: Obj=l_philo[4] State=Philo_thinking
0185068413 ==>Tran: Obj=l_philo[4] Sig=TIMEOUT_SIG Source=Philo_eating New=Philo_thinking
. . . . . .
@endverbatim

As you can see, the difference in readability is quite dramatic.


-------------------------------------------------------------------------------
@section qspy_dict_get Acquiring Dictionaries
The QS Target-resident component generates the dictionary trace records during the initialization of active objects components in the Target code, that is, typically right after the reset. Consequently, the best way to acquire the dictionaries is to capture the trace when the Target performs the reset. This can be done in a couple of ways:
- Start QSPY **before** the Target resets
- Manually reset the Target while QSPY is running (e.g., press a Reset button on the Target board)
- Send the @ref qspy_keyboard "RESET command" to the Target from QSPY while it is running

Either way, the dictionary records should be produced and acquired by the Target. The following listing shows the dictionary records sent by the DPP example application running on the EK-TM4C123GXL board:

@verbatim
C:\qp\qtools\qspy\doxygen>qspy -u -cCOM4
QSPY host application 5.5.0
Copyright (c) Quantum Leaps, state-machine.com
Time Stamp: 150918_113919
-u7701
-cCOM4
-v550
-T4
-O4
-F4
-S2
-E2
-Q1
-P2
-B2
-C2

********** TARGET: QP-Ver: 550, build tstamp:150831_144229
           Obj-Dic: 0000000000004018->QS_RX
           Obj-Dic: 0000000000003B18->l_SysTick_Handler
           Obj-Dic: 0000000000003B19->l_GPIOPortA_IRQHandler
           Usr-Dic: 00000046        ->PHILO_STAT
           Usr-Dic: 00000047        ->COMMAND_STAT
           Obj-Dic: 0000000020000D10->smlPoolSto
           Obj-Dic: 0000000020000CFC->tableQueueSto
           Obj-Dic: 0000000020000C74->philoQueueSto[0]
           Obj-Dic: 0000000020000C88->philoQueueSto[1]
           Obj-Dic: 0000000020000C9C->philoQueueSto[2]
           Obj-Dic: 0000000020000CB0->philoQueueSto[3]
           Obj-Dic: 0000000020000CC4->philoQueueSto[4]
           Obj-Dic: 0000000020000D60->l_philo[0]
           Obj-Dic: 0000000020000D8C->l_philo[0].timeEvt
           Obj-Dic: 0000000020000D9C->l_philo[1]
           Obj-Dic: 0000000020000DC8->l_philo[1].timeEvt
           Obj-Dic: 0000000020000DD8->l_philo[2]
           Obj-Dic: 0000000020000E04->l_philo[2].timeEvt
           Obj-Dic: 0000000020000E14->l_philo[3]
           Obj-Dic: 0000000020000E40->l_philo[3].timeEvt
           Obj-Dic: 0000000020000E50->l_philo[4]
           Obj-Dic: 0000000020000E7C->l_philo[4].timeEvt
           Fun-Dic: 0000000000000A79->Philo_initial
           Fun-Dic: 0000000000000D01->Philo_thinking
           Fun-Dic: 0000000000000C99->Philo_hungry
           Fun-Dic: 0000000000000C45->Philo_eating
           Sig-Dic: 0000000A,Obj=0000000020000D60->HUNGRY_SIG
           Sig-Dic: 0000000B,Obj=0000000020000D60->TIMEOUT_SIG
           INIT : Obj=l_philo[0] Source=NULL Target=Philo_thinking
           ENTRY: Obj=l_philo[0] State=Philo_thinking
0000500000 ==>Init: Obj=l_philo[0] New=Philo_thinking
           Sig-Dic: 0000000A,Obj=0000000020000D9C->HUNGRY_SIG
           Sig-Dic: 0000000B,Obj=0000000020000D9C->TIMEOUT_SIG
           INIT : Obj=l_philo[1] Source=NULL Target=Philo_thinking
           ENTRY: Obj=l_philo[1] State=Philo_thinking
0000500000 ==>Init: Obj=l_philo[1] New=Philo_thinking
           Sig-Dic: 0000000A,Obj=0000000020000DD8->HUNGRY_SIG
           Sig-Dic: 0000000B,Obj=0000000020000DD8->TIMEOUT_SIG
           INIT : Obj=l_philo[2] Source=NULL Target=Philo_thinking
           ENTRY: Obj=l_philo[2] State=Philo_thinking
0000500000 ==>Init: Obj=l_philo[2] New=Philo_thinking
           Sig-Dic: 0000000A,Obj=0000000020000E14->HUNGRY_SIG
           Sig-Dic: 0000000B,Obj=0000000020000E14->TIMEOUT_SIG
           INIT : Obj=l_philo[3] Source=NULL Target=Philo_thinking
           ENTRY: Obj=l_philo[3] State=Philo_thinking
0000500000 ==>Init: Obj=l_philo[3] New=Philo_thinking
           Sig-Dic: 0000000A,Obj=0000000020000E50->HUNGRY_SIG
           Sig-Dic: 0000000B,Obj=0000000020000E50->TIMEOUT_SIG
           INIT : Obj=l_philo[4] Source=NULL Target=Philo_thinking
           ENTRY: Obj=l_philo[4] State=Philo_thinking
0000500000 ==>Init: Obj=l_philo[4] New=Philo_thinking
           Obj-Dic: 0000000020000E90->l_table
           Fun-Dic: 00000000000017A5->QHsm_top
           Fun-Dic: 0000000000000E6D->Table_initial
           Fun-Dic: 0000000000001355->Table_active
           Fun-Dic: 0000000000001145->Table_serving
           Fun-Dic: 0000000000000FFD->Table_paused
           Sig-Dic: 00000005,Obj=0000000000000000->DONE_SIG
           Sig-Dic: 00000004,Obj=0000000000000000->EAT_SIG
           Sig-Dic: 00000006,Obj=0000000000000000->PAUSE_SIG
           Sig-Dic: 00000007,Obj=0000000000000000->SERVE_SIG
           Sig-Dic: 00000008,Obj=0000000000000000->TERMINATE_SIG
           Sig-Dic: 0000000A,Obj=0000000020000E90->HUNGRY_SIG
@endverbatim

Once QSPY acquires the dictionaries, it keeps them in the memory and applies them to display the data in symbolic form (rather than hex addresses).

@note
The dictionaries do not need to be complete to be useful. QSPY simply applies the symbolic information whenever it can find a match in the dictionaries acquired so far. When a dictionary entry is not available, QSPY displays only hex addresses.


-------------------------------------------------------------------------------
@section qspy_dict_save Saving Dictionaries to a File

QSPY can save the dictionaries acquired thus far into a file. This must be triggered by the user (by means of the `d` @ref qspy_keyboard "keyboard command" or from QSpyView menu "File->Save Dictionaries"), because QSPY does not "know" when the dictionaries are "complete", therefore it cannot know when to save them automatically.

On the other hand, QSPY generates automatically the file name for saving dictionaries. This file name has always the form `qspy<target-time-stamp>.dic`, where `<target-time-stamp>` unambiguously identifies the Target build date and time. For example, the Target code last built on August 31, 2015 at 14:42:29 will have the name `qspy150831_144229.dic`.

@attention
The internal addresses of objects can change by every code re-build, so dictionaries are applicable only to the specific Target build and must be freshly re-acquired after every new Target code build.

The dictionaries are saved to a file in ASCII format. The following listing shows the dictionaries from the DPP example application running on the EK-TM4C123GXL board:

@verbatim
-v550
-T4
-O4
-F4
-S2
-E2
-Q1
-P2
-B2
-C2
Obj-Dic:
21 4
0000000000003B18 l_SysTick_Handler
0000000000003B19 l_GPIOPortA_IRQHandler
0000000000004018 QS_RX
0000000020000C74 philoQueueSto[0]
0000000020000C88 philoQueueSto[1]
0000000020000C9C philoQueueSto[2]
0000000020000CB0 philoQueueSto[3]
0000000020000CC4 philoQueueSto[4]
0000000020000CFC tableQueueSto
0000000020000D10 smlPoolSto
0000000020000D60 l_philo[0]
0000000020000D8C l_philo[0].timeEvt
0000000020000D9C l_philo[1]
0000000020000DC8 l_philo[1].timeEvt
0000000020000DD8 l_philo[2]
0000000020000E04 l_philo[2].timeEvt
0000000020000E14 l_philo[3]
0000000020000E40 l_philo[3].timeEvt
0000000020000E50 l_philo[4]
0000000020000E7C l_philo[4].timeEvt
0000000020000E90 l_table
Fun-Dic:
9 4
0000000000000A79 Philo_initial
0000000000000C45 Philo_eating
0000000000000C99 Philo_hungry
0000000000000D01 Philo_thinking
0000000000000E6D Table_initial
0000000000000FFD Table_paused
0000000000001145 Table_serving
0000000000001355 Table_active
00000000000017A5 QHsm_top
Usr-Dic:
2 1
0000000000000046 PHILO_STAT
0000000000000047 COMMAND_STAT
Sig-Dic:
16 4
00000004 0000000000000000 EAT_SIG
00000005 0000000000000000 DONE_SIG
00000006 0000000000000000 PAUSE_SIG
00000007 0000000000000000 SERVE_SIG
00000008 0000000000000000 TERMINATE_SIG
0000000A 0000000020000DD8 HUNGRY_SIG
0000000A 0000000020000E50 HUNGRY_SIG
0000000A 0000000020000E14 HUNGRY_SIG
0000000A 0000000020000D60 HUNGRY_SIG
0000000A 0000000020000D9C HUNGRY_SIG
0000000A 0000000020000E90 HUNGRY_SIG
0000000B 0000000020000E14 TIMEOUT_SIG
0000000B 0000000020000E50 TIMEOUT_SIG
0000000B 0000000020000DD8 TIMEOUT_SIG
0000000B 0000000020000D60 TIMEOUT_SIG
0000000B 0000000020000D9C TIMEOUT_SIG
Msc-Dic:
0 4
@endverbatim


-------------------------------------------------------------------------------
@section qspy_dict_use Using Dictionary File
The dictionary file saved in previous QSPY sessions can be used in two ways:

- you can specify the dictionary file in the `-d` @ref qspy_command "command-line option" to QSPY. In this case QSPY reads the dictionaries before processing any trace records from the Target. (**NOTE:** in this case you don't need to provide any of the upper-case command-line options, because they are read from the dictionary file.) For example: command line: `qspy -dqspy150831_144229.dic` will attempt to read the dictionaries from the specified file.

- you can query the Target information (by means of the `i` @ref qspy_keyboard "keyboard command" or from QSpyView menu "Commands->Query Target Info"). When the Target replies and provides its build-time-stamp, QSPY looks for the corresponding dictionary file in the current directory and if such a file is found, QSPY reads the dictionaries from it. (**NOTE:** this option requires that the Target implements the QS receive channel, QS-RX, so that it can receive commands from QSPY).

@next{qspy_matlab}
*/
/*###########################################################################*/
/**
@page qspy_matlab QSPY MATLAB Support

@tableofcontents

<p>The QSPY host application can also export trace data to <a href="http://www.mathworks.com/products/matlab/" target="_blank" class="extern">MATLAB</a>&reg;, which is a popular numerical computing environment and a high-level technical programming language. Created by The MathWorks, Inc., MATLAB allows easy manipulation and plotting of data represented as matrices.
</p>

@note
The QSPY MATLAB interface is also compatible with the <a href="http://www.gnu.org/software/octave/" target="_blank" class="extern">GNU Octave</a> environment, which is an open source alternative to MATLAB and is compatible with the QSPY MATLAB interface described below.

The following sections provide a reference manual for all 11 the MATLAB matrices generated by the @c qspy.m script. By MATLAB convention, the different variables are put into columns, allowing observations to vary down
through the rows. Therefore, a data set consisting of twenty four time samples of six variables is stored in a matrix of size 24-by-6. The pound sign '#' in a given cell of the matrix represents data available from the target. Other values, represent data added by the @c qspy.m script to allow unambiguous identification of the trace records.

- @ref MATLAB_Q_STATE
- @ref MATLAB_Q_ACTIVE
- @ref MATLAB_Q_EQUEUE
- @ref MATLAB_Q_MPOOL
- @ref MATLAB_Q_NEW
- @ref MATLAB_Q_PUB
- @ref MATLAB_Q_TIME
- @ref MATLAB_Q_INT
- @ref MATLAB_Q_ISR
- @ref MATLAB_Q_MUTEX
- @ref MATLAB_Q_SCHED


-------------------------------------------------------------------------------
@section MATLAB_Q_STATE Q_STATE Matrix
<p>The N-by-6 @c Q_STATE matrix stores all QS records generated by the QEP hierarchical event processor and pertaining to all the state machines in the system. The following table summarizes how the QS records are stored in the matrix:
</p>
<TABLE SUMMARY="Q_STATE Matrix" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>&nbsp;MATLAB index --&gt;</B></TD>
    <TD><B>1</B></TD>
    <TD><B>2</B></TD>
    <TD><B>3</B></TD>
    <TD><B>4</B></TD>
    <TD><B>5</B></TD>
    <TD><B>6</B></TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD><B>QS Record@n |@n V</B></TD>
    <TD><B>Time@n Stamp</B></TD>
    <TD><B>Signal</B></TD>
    <TD><B>State@n Machine@n Object</B></TD>
    <TD><B>Source@n State</B></TD>
    <TD><B>New@n State</B></TD> <TD><B>Event@n Hanlder</B></TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QEP_STATE_ENTRY</TD>
    <TD>NaN</TD>
    <TD>1</TD>
    <TD>#(2)</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QEP_STATE_EXIT</TD>
    <TD>NaN</TD>
    <TD>2</TD>
    <TD>#(2)</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>1</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QEP_STATE_INIT</TD>
    <TD>NaN</TD>
    <TD>3</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QEP_INIT_TRAN</TD>
    <TD>#</TD>
    <TD>3</TD>
    <TD>#(2)</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>1</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QEP_INTERN_TRAN</TD>
    <TD>#</TD>
    <TD>#(1)</TD>
    <TD>#(2)</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QEP_TRAN</TD>
    <TD>#</TD>
    <TD>#(1)</TD>
    <TD>#(2)</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>1</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QEP_IGNORED</TD>
    <TD>#</TD>
    <TD>#(1)</TD>
    <TD>#(2)</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>0</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QEP_DISPATCH</TD>
    <TD>#</TD>
    <TD>#(1)</TD>
    <TD>#(2)</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>0</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QEP_UNHANDLED</TD>
    <TD>NaN</TD>
    <TD>#(1)</TD>
    <TD>#(2)</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>0</TD>
  </TR>
</TABLE>
(1) The valid USER signal is &gt; 3

(2) Per inheritance, an active object is a state machine object as well


The following criteria (index matrices in MATLAB) unambiguously select the QS
records from the @c Q_STATE matrix:

<TABLE SUMMARY="Q_STATE records" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>QS Record</B></TD>
    <TD><B>MATLAB Index Matrix</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QEP_STATE_ENTRY</TD>
    <TD><TT>Q_STATE(:,2) == 1</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QEP_STATE_EXIT</TD>
    <TD><TT>Q_STATE(:,2) == 2</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QEP_STATE_INIT</TD>
    <TD><TT>Q_STATE(:,2) == 3</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QEP_INIT_TRAN</TD>
    <TD><TT>isnan(Q_STATE(:,4))</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QEP_INTERN_TRAN</TD>
    <TD><TT>Q_STATE(:,2) &gt; 3 & isnan(Q_STATE(:,5))</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QEP_TRAN</TD>
    <TD><TT>Q_STATE(:,2) > &gt; & ~isnan(Q_STATE(:,5))</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QEP_IGNORED</TD>
    <TD><TT>~Q_STATE(:,6)</TT></TD>
  </TR>

</TABLE>

For example, the following MATLAB plot shows the timing diagrams for all Philo state machines in the DPP example application made by the `philo_timing.m` script located in the directory `qtools/qspy/matlab` (see Section @ref qspy_files). The vertical axis represents states "thinking" (lowest), "hungry" (middle) and "eating" (top) states.

@image html FigQSPY.01.jpg "Timing diagrams for all Philo state machines."


-------------------------------------------------------------------------------
@section MATLAB_Q_ACTIVE Q_ACTIVE Matrix
<p>The N-by-5 @c Q_ACTIVE matrix stores QS records pertaining to adding/removing active objects and subscribing/unsubscribing to events from active objects. The following table summarizes how the QS records are stored in the matrix:
</p>

<TABLE SUMMARY="Q_ACTIVE Matrix" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>&nbsp;MATLAB index --&gt;</B></TD>
    <TD><B>1</B></TD>
    <TD><B>2</B></TD>
    <TD><B>3</B></TD>
    <TD><B>4</B></TD>
    <TD><B>5</B></TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD><B>QS Record@n |@n V</B></TD>
    <TD><B>Time@n Stamp</B></TD>
    <TD><B>Signal</B></TD>
    <TD><B>Active@n Object</B></TD>
    <TD><B>QF@n Priority</B></TD>
    <TD><B>Delta</B></TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_ACTIVE_ADD</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>+1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_ACTIVE_REMOVE</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>-1</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_ACTIVE_SUBSCRIBE</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>+1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_ACTIVE_UNSUBSCRIBE</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>-1</TD>
  </TR>
</TABLE>

The following criteria (index matrices in MATLAB) unambiguously select the QS records from the @c Q_ACTIVE matrix:

<TABLE SUMMARY="Q_ACTIVE records" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>QS Record</B></TD>
    <TD><B>MATLAB Index Matrix</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_ACTIVE_ADD</TD>
    <TD><TT>isnan(Q_ACTIVE(:,2)) & Q_ACTIVE(:,5) &gt; 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_ACTIVE_REMOVE</TD>
    <TD><TT>isnan(Q_ACTIVE(:,2)) & Q_ACTIVE(:,5) &lt; 0</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_ACTIVE_SUBSCRIBE</TD>
    <TD><TT>isnan(Q_ACTIVE(:,4)) & Q_ACTIVE(:,5) &gt; 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_ACTIVE_UNSUBSCRIBE</TD>
    <TD><TT>isnan(Q_ACTIVE(:,4)) & Q_ACTIVE(:,5) &lt; 0</TT></TD>
  </TR>
</TABLE>


-------------------------------------------------------------------------------
@section MATLAB_Q_EQUEUE Q_EQUEUE Matrix
<p>The N-by-10 @c Q_EQUEUE matrix stores QS records pertaining to queuing events in the QF. Both the active object event queues and the "raw" thread-safe queues are included. The 'nUsed' field denotes the current number of used entries in the queue. The 'Maximum nUsed' filed denotes the maximum number of used entries since initialization (high watermark). Both fields contain the number of used entries in the queues ring-buffer plus one, to account for the extra location at the front of the queue. The following table summarizes how the QS records are stored in the matrix:
</p>

<TABLE SUMMARY="Q_EQUEUE Matrix" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>&nbsp;MATLAB index --&gt;</B></TD>
    <TD><B>1</B></TD>
    <TD><B>2</B></TD>
    <TD><B>3</B></TD>
    <TD><B>4</B></TD>
    <TD><B>5</B></TD>
    <TD><B>6</B></TD>
    <TD><B>7</B></TD>
    <TD><B>8</B></TD>
    <TD><B>9</B></TD>
    <TD><B>10</B></TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD><B>QS Record@n |@n V</B></TD>
    <TD><B>Time@n Stamp</B></TD>
    <TD><B>Sender</B></TD>
    <TD><B>Event@n Queue (1)</B></TD>
    <TD><B>nFree</B></TD>
    <TD><B>Minimum@n Used</B></TD>
    <TD><B>Signal</B></TD>
    <TD><B>Pool ID</B></TD>
    <TD><B>Ref.@n Count</B></TD>
    <TD><B>LIFO</B></TD>
    <TD><B>Delta</B></TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_EQUEUE_INIT</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>0</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>0</TD>
    <TD>0</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_ACTIVE_POST_FIFO</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>0</TD>
    <TD>+1</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_ACTIVE_POST_LIFO</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>1</TD>
    <TD>+1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_ACTIVE_GET</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>0</TD>
    <TD>-1</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_ACTIVE_GET_LAST</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>0</TD>
    <TD>-1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_EQUEUE_POST_FIFO</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>1</TD>
    <TD>#</TD>
    <TD>0</TD>
    <TD>+1</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_EQUEUE_POST_LIFO</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>1</TD>
    <TD>+1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_EQUEUE_GET</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>0</TD>
    <TD>-1</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_EQUEUE_GET_LAST</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>0</TD>
    <TD>-1</TD>
  </TR>
</TABLE>
(1) This field (index 3) is actually the pointer to the ring buffer of the queue.

The following criteria (index matrices in MATLAB) unambiguously select the QS records from the @c Q_EQUEUE matrix:

<TABLE SUMMARY="Q_EQUEUE records" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>QS Record</B></TD>
    <TD><B>MATLAB Index Matrix</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_EQUEUE_INIT</TD>
    <TD><TT>Q_EQUEUE(:,10) == 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_ACTIVE_POST_FIFO</TD>
    <TD><TT>Q_EQUEUE(:,3) == &lt;active obj&gt; & ~Q_EQUEUE(:,9) & Q_EQUEUE(:,10) &gt; 0</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_ACTIVE_POST_LIFO</TD>
    <TD><TT>Q_EQUEUE(:,3) == &lt;active obj&gt; & Q_EQUEUE(:,9) & Q_EQUEUE(:,10) &gt; 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_ACTIVE_GET</TD>
    <TD><TT>Q_EQUEUE(:,3) == &lt;active obj&gt; & ~isnan(Q_EQUEUE(:,4) & Q_EQUEUE(:,10) &lt; 0</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_ACTIVE_GET_LAST</TD>
    <TD><TT>Q_EQUEUE(:,3) == &lt;active obj&gt; & isnan(Q_EQUEUE(:,4) & Q_EQUEUE(:,10) &lt; 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_EQUEUE_POST_FIFO</TD>
    <TD><TT>Q_EQUEUE(:,3) == &lt;raw queue&gt; & ~Q_EQUEUE(:,9) & Q_EQUEUE(:,10) &gt; 0</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_EQUEUE_POST_LIFO</TD>
    <TD><TT>Q_EQUEUE(:,3) == &lt;raw queue&gt; & Q_EQUEUE(:,9) & Q_EQUEUE(:,10) &gt; 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_EQUEUE_GET</TD>
    <TD><TT>Q_EQUEUE(:,3) == &lt;raw queue&gt; & ~isnan(Q_EQUEUE(:,4) & Q_EQUEUE(:,10) &lt; 0</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_EQUEUE_GET_LAST</TD>
    <TD><TT>Q_EQUEUE(:,3) == &lt;raw queue&gt; & isnan(Q_EQUEUE(:,4) & Q_EQUEUE(:,10) &lt; 0</TT></TD>
  </TR>
</TABLE>


-------------------------------------------------------------------------------
@section MATLAB_Q_MPOOL Q_MPOOL Matrix
<p>The N-by-5 @c Q_MPOOL matrix stores QS records pertaining to memory pools in the QF. The 'nFree' field denotes the current number of free blocks in the event pool. The 'Minimum nFree' filed denotes the minimal number of free blocks since initialization (low watermark). The following table summarizes how the QS records are stored in the matrix:
</p>

<TABLE SUMMARY="Q_MPOOL Matrix" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>&nbsp;MATLAB index --&gt;</B></TD>
    <TD><B>1</B></TD>
    <TD><B>2</B></TD>
    <TD><B>3</B></TD>
    <TD><B>4</B></TD>
    <TD><B>5</B></TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD><B>QS Record@n |@n V</B></TD>
    <TD><B>Time@n Stamp</B></TD>
    <TD><B>Pool@n Object</B></TD>
    <TD><B>nFree</B></TD>
    <TD><B>Minimal@n nFree</B></TD>
    <TD><B>Delta</B></TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_MPOOL_INIT</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>0</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_MPOOL_GET</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>-1</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_MPOOL_PUT</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>+1</TD>
  </TR>
</TABLE>

The cumulative sum over the 'Delta' column should not have any long-time trends, because this would indicate a leak from the pool. The following picture shows the plot for the test data.

@image html FigQSPY.02.jpg "Plot stairs(Q_MPOOL(:,1), cumsum(Q_MPOOL(:,5)))"

The following criteria (index matrices in MATLAB) unambiguously select the QS
records from the @c Q_MPOOL matrix:

<TABLE SUMMARY="Q_MPOOL records" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>QS Record</B></TD>
    <TD><B>MATLAB Index Matrix</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_MPOOL_INIT</TD>
    <TD><TT>Q_MPOOL(:,5) == 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_MPOOL_GET</TD>
    <TD><TT>Q_MPOOL(:,5) &lt; 0</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_MPOOL_PUT</TD>
    <TD><TT>Q_MPOOL(:,5) &gt; 0</TT></TD>
  </TR>
</TABLE>


-------------------------------------------------------------------------------
@section MATLAB_Q_NEW Q_NEW Matrix
<p>The N-by-6 @c Q_NEW matrix stores QS records pertaining to dynamic event allocation and automatic event recycling (garbage collection) in the QF. The following table summarizes how the QS records are stored in the matrix:
</p>

<TABLE SUMMARY="Q_NEW Matrix" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>&nbsp;MATLAB index --&gt;</B></TD>
    <TD><B>1</B></TD>
    <TD><B>2</B></TD>
    <TD><B>3</B></TD>
    <TD><B>4</B></TD>
    <TD><B>5</B></TD>
    <TD><B>6</B></TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD><B>QS Record@n |@n V</B></TD>
    <TD><B>Time@n Stamp</B></TD>
    <TD><B>Signal</B></TD>
    <TD><B>PoolID</B></TD>
    <TD><B>Ref.@n Count</B></TD>
    <TD><B>Event@n Size</B></TD>
    <TD><B>Delta</B></TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_NEW</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>+1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_GC_ATTEMPT</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>0</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_GC</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>-1</TD>
  </TR>
</TABLE>

The cumulative sum over the 'Delta' column should not have any long-time trends, because this would indicate event leak. The following picture shows the plot for the test data.

@image html FigQSPY.03.jpg "Plot stairs(Q_NEW(:,1), cumsum(Q_NEW(:,6)))"

The following criteria (index matrices in MATLAB) unambiguously select the QS
records from the @c Q_NEW matrix:

<TABLE SUMMARY="Q_NEW records" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>QS Record</B></TD>
    <TD><B>MATLAB Index Matrix</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_NEW</TD>
    <TD><TT>%Q_NEW(:,6) &gt; 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_GC_ATTEMPT</TD>
    <TD><TT>%Q_NEW(:,6) == 0</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_GC</TD>
    <TD><TT>%Q_NEW(:,6) &lt; 0</TT></TD>
  </TR>
</TABLE>


-------------------------------------------------------------------------------
@section MATLAB_Q_PUB Q_PUB Matrix
<p>The N-by-7 @c Q_PUB matrix stores QS records pertaining to publishing events in QF. The following table summarizes how the QS records are stored in the matrix:
</p>

<TABLE SUMMARY="Q_PUB Matrix" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>&nbsp;MATLAB index --&gt;</B></TD>
    <TD><B>1</B></TD>
    <TD><B>2</B></TD>
    <TD><B>3</B></TD>
    <TD><B>4</B></TD>
    <TD><B>5</B></TD>
    <TD><B>6</B></TD>
    <TD><B>7</B></TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD><B>QS Record@n |@n V</B></TD>
    <TD><B>Time@n Stamp</B></TD>
    <TD><B>Sender</B></TD>
    <TD><B>Signal</B></TD>
    <TD><B>PoolID</B></TD>
    <TD><B>Ref.@n Count</B></TD>
    <TD><B># Events@n Multicast</B></TD>
    <TD><B>Delta</B></TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_PUBLISH</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
  </TR>
</TABLE>

The following criteria (index matrices in MATLAB) unambiguously select the QS
records from the @c Q_PUB matrix:

<TABLE SUMMARY="Q_PUB records" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>QS Record</B></TD>
    <TD><B>MATLAB Index Matrix</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_PUBLISH</TD>
    <TD><TT>Q_PUB(:,7) &gt; 0</TT></TD>
  </TR>
</TABLE>


-------------------------------------------------------------------------------
@section MATLAB_Q_TIME Q_TIME Matrix
<p>The N-by-7 @c Q_TIME matrix stores QS records pertaining to time events in QF. The following table summarizes how the QS records are stored in the matrix:
</p>

<TABLE SUMMARY="Q_TIME Matrix" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>&nbsp;MATLAB index --&gt;</B></TD>
    <TD><B>1</B></TD>
    <TD><B>2</B></TD>
    <TD><B>3</B></TD>
    <TD><B>4</B></TD>
    <TD><B>5</B></TD>
    <TD><B>6</B></TD>
    <TD><B>7</B></TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD><B>QS Record@n |@n V</B></TD>
    <TD><B>Time@n Stamp</B></TD>
    <TD><B>QTimeEvt@n Object</B></TD>
    <TD><B>Signal</B></TD>
    <TD><B>QActive@n Object</B></TD>
    <TD><B>QTimeEvt@n Counter</B></TD>
    <TD><B>QTimeEvt@n Interval</B></TD>
    <TD><B>QTimeEvt@n Delta</B></TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_TICK</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>#(1)</TD>
    <TD>NaN</TD>
    <TD>0</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_TIMEEVT_ARM</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>+1</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_TIMEEVT_DISARM</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>-1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_TIMEEVT_AUTO_DISARM</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>-1</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_TIMEEVT_DISARM_ATTEMPT</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>0</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_TIMEEVT_REARM</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#(2)</TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_TIMEEVT_POST</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>NaN</TD>
    <TD>NaN</TD>
    <TD>0</TD>
  </TR>
</TABLE>
(1) For #QS_QF_TICK record this matrix element contains the Tick Counter.

(2) For #QS_QF_TIMEEVT_REARM event this matrix element is 0 if the time event was disarmed and rearmed again, and 1 if the time event was only armed.

The cumulative sum over the 'Delta' column indicates the total number of armed time events at any given time. The following picture shows the plot for the test data:

@image html FigQSPY.04.jpg "Plot stairs(Q_TIME(:,1), cumsum(Q_TIME(:,7)))"

The following criteria (index matrices in MATLAB) unambiguously select the QS
records from the @c Q_TIME matrix:

<TABLE SUMMARY="Q_TIME records" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>QS Record</B></TD>
    <TD><B>MATLAB Index Matrix</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_TICK</TD>
    <TD><TT>isnan(Q_TIME(:,2))</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_TIMEEVT_ARM</TD>
    <TD><TT>Q_TIME(:,7) &gt; 0</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_TIMEEVT_DISARM</TD>
    <TD><TT>~isnan(Q_TIME(:,1)) & Q_TIME(:,7) &lt; 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_TIMEEVT_AUTO_DISARM</TD>
    <TD><TT>isnan(Q_TIME(:,1)) & Q_TIME(:,7) &lt; 0</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_TIMEEVT_DISARM_ATTEMPT</TD>
    <TD><TT>isnan(Q_TIME(:,3)) & isnan(Q_TIME(:,5)) & Q_TIME(:,7) == 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_TIMEEVT_REARM</TD>
    <TD><TT>isnan(Q_TIME(:,3)) & ~isnan(Q_TIME(:,5))</TT></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_TIMEEVT_POST</TD>
    <TD><TT>~isnan(Q_TIME(:,3)) & ~isnan(Q_TIME(:,4))</TT></TD>
  </TR>
</TABLE>


-------------------------------------------------------------------------------
@section MATLAB_Q_INT Q_INT Matrix
<p>The N-by-3 @c Q_INT matrix stores QS records pertaining to interrupt disabling and enabling. The following table summarizes how the QS records are stored in the matrix:
</p>

<TABLE SUMMARY="Q_INT Matrix" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>&nbsp;MATLAB index --&gt;</B></TD>
    <TD><B>1</B></TD>
    <TD><B>2</B></TD>
    <TD><B>3</B></TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD><B>QS Record@n |@n V</B></TD>
    <TD><B>Time@n Stamp</B></TD>
    <TD><B>Interrupt@n Nesting</B></TD>
    <TD><B>Nesting@n Delta</B></TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_INT_DISABLE</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>+1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_INT_ENABLE</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>-1</TD>
  </TR>
</TABLE>

The cumulative sum over the 'Delta' column indicates interrupt lock nesting
and should closely follow column 2.

The following criteria (index matrices in MATLAB) unambiguously select the QS
records from the @c Q_INT matrix:

<TABLE SUMMARY="Q_INT records" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>QS Record</B></TD>
    <TD><B>MATLAB Index Matrix</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_INT_DISABLE</TD>
    <TD><TT>Q_INT(:,3) &gt; 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_INT_ENABLE</TD>
    <TD><TT>Q_INT(:,3) &lt; 0</TT></TD>
  </TR>
</TABLE>


-------------------------------------------------------------------------------
@section MATLAB_Q_ISR Q_ISR Matrix
<p>The N-by-4 @c Q_ISR matrix stores QS records pertaining to interrupt entry and exit. The following table summarizes how the QS records are stored in the matrix:
</p>

<TABLE SUMMARY="Q_ISR Matrix" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>&nbsp;MATLAB index --&gt;</B></TD>
    <TD><B>1</B></TD>
    <TD><B>2</B></TD>
    <TD><B>3</B></TD>
    <TD><B>4</B></TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD><B>QS Record@n |@n V</B></TD>
    <TD><B>Time@n Stamp</B></TD>
    <TD><B>Interrupt@n Nesting</B></TD>
    <TD><B>ISR@n Priority</B></TD>
    <TD><B>Nesting@n Delta</B></TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QF_ISR_ENTRY</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>+1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QF_ISR_EXIT</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>-1</TD>
  </TR>
</TABLE>

The cumulative sum over the 'Delta' column indicates interrupt nesting level and should closely follow column 2.

The following criteria (index matrices in MATLAB) unambiguously select the QS records from the @c Q_ISR matrix:

<TABLE SUMMARY="Q_ISR records" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>QS Record</B></TD>
    <TD><B>MATLAB Index Matrix</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QF_ISR_ENTRY</TD>
    <TD><TT>Q_ISR(:,4) &gt; 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QF_ISR_EXIT</TD>
    <TD><TT>Q_ISR(:,4) &lt; 0</TT></TD>
  </TR>
</TABLE>


-------------------------------------------------------------------------------
@section MATLAB_Q_MUTEX Q_MUTEX Matrix
<p>The N-by-4 @c Q_MUTEX matrix stores QS records pertaining to the priority-ceiling mutex activity in QK. The following table summarizes how the QS records are stored in the matrix:
</p>

<TABLE SUMMARY="Q_MUTEX Matrix" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>&nbsp;MATLAB index --&gt;</B></TD>
    <TD><B>1</B></TD>
    <TD><B>2</B></TD>
    <TD><B>3</B></TD>
    <TD><B>4</B></TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD><B>QS Record@n |@n V</B></TD>
    <TD><B>Time@n Stamp</B></TD>
    <TD><B>Original@n Priority</B></TD>
    <TD><B>Priority@n Ceiling</B></TD>
    <TD><B>Nesting@n Delta</B></TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QK_MUTEX_LOCK</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>+1</TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD>@c #QS_QK_MUTEX_UNLOCK</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>-1</TD>
  </TR>
</TABLE>


The cumulative sum over the 'Delta' column indicates QK scheduler lock nesting level.

@image html FigQSPY.05.jpg "Plot stairs(Q_MUTEX(:,1), cumsum(Q_MUTEX(:,4)), 'r') (red)"


The following criteria (index matrices in MATLAB) unambiguously select the QS records from the @c Q_ISR matrix:

<TABLE SUMMARY="Q_ISR records" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>QS Record</B></TD>
    <TD><B>MATLAB Index Matrix</B></TD>
  </TR>

  <TR bgColor="#f0f0f0">
    <TD>@c #QS_QK_MUTEX_LOCK</TD>
    <TD><TT>Q_MUTEX(:,4) &gt; 0</TT></TD>
  </TR>

  <TR bgColor="#c0c0c0">
    <TD>@c #QS_QK_MUTEX_UNLOCK</TD>
    <TD><TT>Q_MUTEX(:,4) &lt; 0</TT></TD>
  </TR>
</TABLE>


-------------------------------------------------------------------------------
@section MATLAB_Q_SCHED Q_SCHED Matrix
<p>The N-by-3 @c Q_SCHED matrix stores QS records pertaining to scheduling next task in QK. The following table summarizes how the QS records are stored in the matrix:
</p>

<TABLE SUMMARY="Q_MUTEX Matrix" cellSpacing=4 cellPadding=1 border=0
ALIGN="center">
  <TR bgColor="#c8cedc" ALIGN="center">
    <TD><B>&nbsp;MATLAB index --&gt;</B></TD>
    <TD><B>1</B></TD>
    <TD><B>2</B></TD>
    <TD><B>3</B></TD>
  </TR>

  <TR bgColor="#f0f0f0" ALIGN="center">
    <TD><B>QS Record@n |@n V</B></TD>
    <TD><B>Time@n Stamp</B></TD>
    <TD><B>Preempted@n Priority</B></TD>
    <TD><B>New@n Priority</B></TD>
  </TR>

  <TR bgColor="#c0c0c0" ALIGN="center">
    <TD>@c #QS_QK_SCHEDULE</TD>
    <TD>#</TD>
    <TD>#</TD>
    <TD>#</TD>
  </TR>
</TABLE>


@next{qspy_mscgen}
*/
/*###########################################################################*/
/**
@page qspy_mscgen QSPY MscGen Support

The QSPY host application can also save the tracing data in the format suitable for the <a href="http://www.mcternan.me.uk/mscgen/" target="_blank" class="extern">MscGen utility</a> to generate <strong>sequence diagrams</strong>.

@note The MscGen utility is also available in the <b>Qtools</b> collection (the same that contains QSPY itself, see @ref install "Installing").

To generate an MscGen file, you need to invoke QSPY with  the `-g` @ref qspy_command "command-line option", or to hit the `g` @ref qspy_keyboard "key-stroke" while QSPY is running. 


@note
The generation of sequence diagrams relies on the following QS trace records being enabled: #QS_QF_ACTIVE_POST_FIFO, #QS_QF_ACTIVE_POST_LIFO. Additional annotations of the sequence diagrams are also available if the following QS trace records are enabled: #QS_QF_PUBLISH, #QS_QF_TICK, and #QS_QEP_TRAN. 

Subsequently, you need to invoke the MscGen utility to convert the generated file to graphical format, such as .PNG, .EPS, .SVG, or .ISMAP. For example, the following command generates a sequence diagram in .SVG from the dpp.msc file.

@verbatim
mscgen -Tsvg -idpp.msc
@endverbatim

The following screen shot shows a sequence diagram generated from the Dining Philosophers Problem (DPP) application. The .MSC file has been converted to .SVG and viewed in a web browser (Google Chrome in this case).

@image html mscgen_dpp.gif

@note
The numbers proceeding the signal names in the diagram are the Target time-stamps.

@next{qspyview}
*/
