
O
Command: %s
53*	vivadotcl2

opt_design2default:defaultZ4-113h px� 
�
@Attempting to get a license for feature '%s' and/or device '%s'
308*common2"
Implementation2default:default2
xc7z0102default:defaultZ17-347h px� 
�
0Got license for feature '%s' and/or device '%s'
310*common2"
Implementation2default:default2
xc7z0102default:defaultZ17-349h px� 
n
,Running DRC as a precondition to command %s
22*	vivadotcl2

opt_design2default:defaultZ4-22h px� 
R

Starting %s Task
103*constraints2
DRC2default:defaultZ18-103h px� 
P
Running DRC with %s threads
24*drc2
82default:defaultZ23-27h px� 
U
DRC finished with %s
272*project2
0 Errors2default:defaultZ1-461h px� 
d
BPlease refer to the DRC report (report_drc) for more information.
274*projectZ1-462h px� 
�

%s
*constraints2�
�Time (s): cpu = 00:00:00.08 ; elapsed = 00:00:00.07 . Memory (MB): peak = 1322.457 ; gain = 69.023 ; free physical = 6738 ; free virtual = 274422default:defaulth px� 
E
%Done setting XDC timing constraints.
35*timingZ38-35h px� 
a

Starting %s Task
103*constraints2&
Logic Optimization2default:defaultZ18-103h px� 
@
+Implement Debug Cores | Checksum: b55e5163
*commonh px� 
i

Phase %s%s
101*constraints2
1 2default:default2
Retarget2default:defaultZ18-101h px� 
u
)Pushed %s inverter(s) to %s load pin(s).
98*opt2
02default:default2
02default:defaultZ31-138h px� 
K
Retargeted %s cell(s).
49*opt2
02default:defaultZ31-49h px� 
<
'Phase 1 Retarget | Checksum: 192aa1400
*commonh px� 
�

%s
*constraints2�
�Time (s): cpu = 00:00:00.17 ; elapsed = 00:00:00.17 . Memory (MB): peak = 1715.949 ; gain = 0.000 ; free physical = 6390 ; free virtual = 271012default:defaulth px� 
u

Phase %s%s
101*constraints2
2 2default:default2(
Constant Propagation2default:defaultZ18-101h px� 
u
)Pushed %s inverter(s) to %s load pin(s).
98*opt2
02default:default2
02default:defaultZ31-138h px� 
K
Eliminated %s cells.
10*opt2
1632default:defaultZ31-10h px� 
H
3Phase 2 Constant Propagation | Checksum: 20107063e
*commonh px� 
�

%s
*constraints2�
�Time (s): cpu = 00:00:00.51 ; elapsed = 00:00:00.37 . Memory (MB): peak = 1715.949 ; gain = 0.000 ; free physical = 6389 ; free virtual = 271002default:defaulth px� 
f

Phase %s%s
101*constraints2
3 2default:default2
Sweep2default:defaultZ18-101h px� 
V
 Eliminated %s unconnected nets.
12*opt2
2012default:defaultZ31-12h px� 
W
!Eliminated %s unconnected cells.
11*opt2
1932default:defaultZ31-11h px� 
9
$Phase 3 Sweep | Checksum: 1bda0c407
*commonh px� 
�

%s
*constraints2�
�Time (s): cpu = 00:00:01 ; elapsed = 00:00:00.73 . Memory (MB): peak = 1715.949 ; gain = 0.000 ; free physical = 6388 ; free virtual = 271002default:defaulth px� 
a

Starting %s Task
103*constraints2&
Connectivity Check2default:defaultZ18-103h px� 
�

%s
*constraints2�
�Time (s): cpu = 00:00:00 ; elapsed = 00:00:00.01 . Memory (MB): peak = 1715.949 ; gain = 0.000 ; free physical = 6388 ; free virtual = 271002default:defaulth px� 
J
5Ending Logic Optimization Task | Checksum: 1bda0c407
*commonh px� 
�

%s
*constraints2�
�Time (s): cpu = 00:00:01 ; elapsed = 00:00:00.75 . Memory (MB): peak = 1715.949 ; gain = 0.000 ; free physical = 6388 ; free virtual = 271002default:defaulth px� 
a

Starting %s Task
103*constraints2&
Power Optimization2default:defaultZ18-103h px� 
s
7Will skip clock gating for clocks with period < %s ns.
114*pwropt2
2.002default:defaultZ34-132h px� 
J
5Ending Power Optimization Task | Checksum: 1bda0c407
*commonh px� 
�

%s
*constraints2�
�Time (s): cpu = 00:00:00.01 ; elapsed = 00:00:00.01 . Memory (MB): peak = 1715.949 ; gain = 0.000 ; free physical = 6388 ; free virtual = 271002default:defaulth px� 
Z
Releasing license: %s
83*common2"
Implementation2default:defaultZ17-83h px� 
�
G%s Infos, %s Warnings, %s Critical Warnings and %s Errors encountered.
28*	vivadotcl2
202default:default2
02default:default2
02default:default2
02default:defaultZ4-41h px� 
\
%s completed successfully
29*	vivadotcl2

opt_design2default:defaultZ4-42h px� 
�
r%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s ; free physical = %s ; free virtual = %s
480*common2 
opt_design: 2default:default2
00:00:082default:default2
00:00:082default:default2
1715.9492default:default2
462.5162default:default2
63882default:default2
271002default:defaultZ17-722h px� 
D
Writing placer database...
1603*designutilsZ20-1893h px� 
=
Writing XDEF routing.
211*designutilsZ20-211h px� 
J
#Writing XDEF routing logical nets.
209*designutilsZ20-209h px� 
J
#Writing XDEF routing special nets.
210*designutilsZ20-210h px� 
�
r%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s ; free physical = %s ; free virtual = %s
480*common2)
Write XDEF Complete: 2default:default2
00:00:00.122default:default2
00:00:00.052default:default2
1747.9652default:default2
0.0002default:default2
63862default:default2
270992default:defaultZ17-722h px� 
P
Running DRC with %s threads
24*drc2
82default:defaultZ23-27h px� 
�
#The results of DRC are in file %s.
168*coretcl2�
�/home/catalin/M.E.Electronics/Project_2/SEM2PRO/Vivado/can_network_v3/can_network_v3.runs/impl_1/dsgn_can_network_v3_wrapper_drc_opted.rpt�/home/catalin/M.E.Electronics/Project_2/SEM2PRO/Vivado/can_network_v3/can_network_v3.runs/impl_1/dsgn_can_network_v3_wrapper_drc_opted.rpt2default:default8Z2-168h px� 


End Record