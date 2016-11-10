<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.7.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="6" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="5" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="inductor-neosid">
<description>&lt;b&gt;Neosid Chokes and Transformers&lt;/b&gt;&lt;p&gt;

Based on the following sources:
&lt;ul&gt;
&lt;li&gt;Electronic Component Book, Part 2 : Chokes, Fixed Value Inductors
&lt;li&gt;Part 3 : Filters, Coil Assemblies, Thermoplastic Parts
&lt;li&gt;Part 4 : SMD Filters, Coils, Fixed Value Inductors
&lt;li&gt;www.neosid.de
&lt;/ul&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="Z15/05">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding counter clockwise</description>
<wire x1="-3.25" y1="-1.4" x2="-2.925" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="-1.35" y1="-1.4" x2="3.25" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="3.25" y1="-1.4" x2="3.25" y2="1.4" width="0.2032" layer="21"/>
<wire x1="3.25" y1="1.4" x2="2.925" y2="1.4" width="0.2032" layer="21"/>
<wire x1="1.35" y1="1.4" x2="-3.25" y2="1.4" width="0.2032" layer="21"/>
<wire x1="-3.25" y1="1.4" x2="-3.25" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="-2.025" y1="-1.125" x2="-1.8" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-1.575" y1="-1.125" x2="-1.35" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-1.125" y1="-1.125" x2="-0.9" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-0.675" y1="-1.125" x2="-0.45" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-0.225" y1="-1.125" x2="0" y2="1.125" width="0.4572" layer="51"/>
<wire x1="0.225" y1="-1.125" x2="0.45" y2="1.125" width="0.4572" layer="51"/>
<wire x1="0.675" y1="-1.125" x2="0.9" y2="1.125" width="0.4572" layer="51"/>
<wire x1="1.125" y1="-1.125" x2="1.35" y2="1.125" width="0.4572" layer="51"/>
<wire x1="1.575" y1="-1.125" x2="1.8" y2="1.125" width="0.4572" layer="51"/>
<wire x1="2.025" y1="-1.125" x2="2.25" y2="1.125" width="0.4572" layer="51"/>
<wire x1="2.8" y1="1.4" x2="1.475" y2="1.4" width="0.2032" layer="51"/>
<wire x1="-2.8" y1="-1.4" x2="-1.475" y2="-1.4" width="0.2032" layer="51"/>
<pad name="1" x="-2.15" y="-1.25" drill="0.7" shape="octagon"/>
<pad name="2" x="2.15" y="1.25" drill="0.7" shape="octagon"/>
<text x="-3.1" y="2.225" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.1" y="-3.475" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z15/07">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding counter clockwise</description>
<wire x1="-3.25" y1="-1.4" x2="-1.6" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-1.6" y1="-1.4" x2="3.25" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="3.25" y1="-1.4" x2="3.25" y2="1.4" width="0.2032" layer="21"/>
<wire x1="3.25" y1="1.4" x2="1.6" y2="1.4" width="0.2032" layer="51"/>
<wire x1="1.6" y1="1.4" x2="-3.25" y2="1.4" width="0.2032" layer="21"/>
<wire x1="-3.25" y1="1.4" x2="-3.25" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="-2.4" y1="-1.2" x2="-2" y2="1.2" width="0.4064" layer="51"/>
<wire x1="-2" y1="-1.2" x2="-1.6" y2="1.2" width="0.4064" layer="51"/>
<wire x1="-1.6" y1="-1.2" x2="-1.2" y2="1.2" width="0.4064" layer="51"/>
<wire x1="-1.2" y1="-1.2" x2="-0.8" y2="1.2" width="0.4064" layer="51"/>
<wire x1="-0.8" y1="-1.2" x2="-0.4" y2="1.2" width="0.4064" layer="51"/>
<wire x1="-0.4" y1="-1.2" x2="0" y2="1.2" width="0.4064" layer="51"/>
<wire x1="0" y1="-1.2" x2="0.4" y2="1.2" width="0.4064" layer="51"/>
<wire x1="0.4" y1="-1.2" x2="0.8" y2="1.2" width="0.4064" layer="51"/>
<wire x1="0.8" y1="-1.2" x2="1.2" y2="1.2" width="0.4064" layer="51"/>
<wire x1="1.2" y1="-1.2" x2="1.6" y2="1.2" width="0.4064" layer="51"/>
<wire x1="1.6" y1="-1.2" x2="2" y2="1.2" width="0.4064" layer="51"/>
<wire x1="2" y1="-1.2" x2="2.4" y2="1.2" width="0.4064" layer="51"/>
<pad name="1" x="-2.4" y="-1.3" drill="0.7" shape="octagon"/>
<pad name="2" x="2.4" y="1.3" drill="0.7" shape="octagon"/>
<text x="-3.1" y="2.225" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.1" y="-3.475" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z15/1">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding counter clockwise</description>
<wire x1="-3.25" y1="-1.4" x2="-1.75" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-1.75" y1="-1.4" x2="3.25" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="3.25" y1="-1.4" x2="3.25" y2="0.7" width="0.2032" layer="21"/>
<wire x1="3.25" y1="0.7" x2="3.25" y2="1.4" width="0.2032" layer="51"/>
<wire x1="3.25" y1="1.4" x2="1.75" y2="1.4" width="0.2032" layer="51"/>
<wire x1="1.75" y1="1.4" x2="-3.25" y2="1.4" width="0.2032" layer="21"/>
<wire x1="-3.25" y1="1.4" x2="-3.25" y2="-0.7" width="0.2032" layer="21"/>
<wire x1="-3.25" y1="-0.7" x2="-3.25" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-2.8" y1="-1.05" x2="-2.45" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-2.45" y1="-1.05" x2="-2.1" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-2.1" y1="-1.05" x2="-1.75" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-1.75" y1="-1.05" x2="-1.4" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-1.4" y1="-1.05" x2="-1.05" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-1.05" y1="-1.05" x2="-0.7" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-0.7" y1="-1.05" x2="-0.35" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-0.35" y1="-1.05" x2="0" y2="1.05" width="0.3556" layer="51"/>
<wire x1="0" y1="-1.05" x2="0.35" y2="1.05" width="0.3556" layer="51"/>
<wire x1="0.35" y1="-1.05" x2="0.7" y2="1.05" width="0.3556" layer="51"/>
<wire x1="0.7" y1="-1.05" x2="1.05" y2="1.05" width="0.3556" layer="51"/>
<wire x1="1.05" y1="-1.05" x2="1.4" y2="1.05" width="0.3556" layer="51"/>
<wire x1="1.4" y1="-1.05" x2="1.75" y2="1.05" width="0.3556" layer="51"/>
<wire x1="1.75" y1="-1.05" x2="2.1" y2="1.05" width="0.3556" layer="51"/>
<wire x1="2.1" y1="-1.05" x2="2.45" y2="1.05" width="0.3556" layer="51"/>
<wire x1="2.45" y1="-1.05" x2="2.8" y2="1.05" width="0.3556" layer="51"/>
<pad name="1" x="-2.75" y="-1.3" drill="0.6" shape="octagon"/>
<pad name="2" x="2.75" y="1.3" drill="0.6" shape="octagon"/>
<text x="-3.227" y="1.844" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.084" y="-2.967" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z15/15">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding counter clockwise</description>
<wire x1="-4.8" y1="-1.4" x2="-4.8" y2="1.4" width="0.2032" layer="21"/>
<wire x1="-4.8" y1="1.4" x2="2.925" y2="1.4" width="0.2032" layer="21"/>
<wire x1="2.925" y1="1.4" x2="4.8" y2="1.4" width="0.2032" layer="51"/>
<wire x1="4.8" y1="1.4" x2="4.8" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="4.8" y1="-1.4" x2="-2.925" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="-2.925" y1="-1.4" x2="-4.8" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-3.825" y1="-1.125" x2="-3.6" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-3.375" y1="-1.125" x2="-3.15" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-2.925" y1="-1.125" x2="-2.7" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-2.475" y1="-1.125" x2="-2.25" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-2.025" y1="-1.125" x2="-1.8" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-1.575" y1="-1.125" x2="-1.35" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-1.125" y1="-1.125" x2="-0.9" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-0.675" y1="-1.125" x2="-0.45" y2="1.125" width="0.4572" layer="51"/>
<wire x1="-0.225" y1="-1.125" x2="0" y2="1.125" width="0.4572" layer="51"/>
<wire x1="0.225" y1="-1.125" x2="0.45" y2="1.125" width="0.4572" layer="51"/>
<wire x1="0.675" y1="-1.125" x2="0.9" y2="1.125" width="0.4572" layer="51"/>
<wire x1="1.125" y1="-1.125" x2="1.35" y2="1.125" width="0.4572" layer="51"/>
<wire x1="1.575" y1="-1.125" x2="1.8" y2="1.125" width="0.4572" layer="51"/>
<wire x1="2.025" y1="-1.125" x2="2.25" y2="1.125" width="0.4572" layer="51"/>
<wire x1="2.475" y1="-1.125" x2="2.7" y2="1.125" width="0.4572" layer="51"/>
<wire x1="2.925" y1="-1.125" x2="3.15" y2="1.125" width="0.4572" layer="51"/>
<wire x1="3.375" y1="-1.125" x2="3.6" y2="1.125" width="0.4572" layer="51"/>
<wire x1="3.825" y1="-1.125" x2="4.05" y2="1.125" width="0.4572" layer="51"/>
<pad name="1" x="-3.9" y="-1.3" drill="0.6" shape="octagon"/>
<pad name="2" x="3.9" y="1.3" drill="0.6" shape="octagon"/>
<text x="-4.37" y="1.717" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.1" y="-2.967" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z15/25">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding counter clockwise</description>
<wire x1="-4.8" y1="-1.25" x2="-2.8" y2="-1.25" width="0.2032" layer="51"/>
<wire x1="-2.8" y1="-1.25" x2="4.8" y2="-1.25" width="0.2032" layer="21"/>
<wire x1="4.8" y1="-1.25" x2="4.8" y2="1.25" width="0.2032" layer="21"/>
<wire x1="4.8" y1="1.25" x2="2.8" y2="1.25" width="0.2032" layer="51"/>
<wire x1="2.8" y1="1.25" x2="-4.8" y2="1.25" width="0.2032" layer="21"/>
<wire x1="-4.8" y1="1.25" x2="-4.8" y2="-1.25" width="0.2032" layer="21"/>
<wire x1="-3.85" y1="-1.4" x2="-3.5" y2="1.05" width="0.3048" layer="51"/>
<wire x1="-3.5" y1="-1.05" x2="-3.15" y2="1.05" width="0.3048" layer="51"/>
<wire x1="-3.15" y1="-1.05" x2="-2.8" y2="1.05" width="0.3048" layer="51"/>
<wire x1="-2.8" y1="-1.05" x2="-2.45" y2="1.05" width="0.3048" layer="51"/>
<wire x1="-2.45" y1="-1.05" x2="-2.1" y2="1.05" width="0.3048" layer="51"/>
<wire x1="-2.1" y1="-1.05" x2="-1.75" y2="1.05" width="0.3048" layer="51"/>
<wire x1="-1.75" y1="-1.05" x2="-1.4" y2="1.05" width="0.3048" layer="51"/>
<wire x1="-1.4" y1="-1.05" x2="-1.05" y2="1.05" width="0.3048" layer="51"/>
<wire x1="-1.05" y1="-1.05" x2="-0.7" y2="1.05" width="0.3048" layer="51"/>
<wire x1="-0.7" y1="-1.05" x2="-0.35" y2="1.05" width="0.3048" layer="51"/>
<wire x1="-0.35" y1="-1.05" x2="0" y2="1.05" width="0.3048" layer="51"/>
<wire x1="0" y1="-1.05" x2="0.35" y2="1.05" width="0.3048" layer="51"/>
<wire x1="0.35" y1="-1.05" x2="0.7" y2="1.05" width="0.3048" layer="51"/>
<wire x1="0.7" y1="-1.05" x2="1.05" y2="1.05" width="0.3048" layer="51"/>
<wire x1="1.05" y1="-1.05" x2="1.4" y2="1.05" width="0.3048" layer="51"/>
<wire x1="1.4" y1="-1.05" x2="1.75" y2="1.05" width="0.3048" layer="51"/>
<wire x1="1.75" y1="-1.05" x2="2.1" y2="1.05" width="0.3048" layer="51"/>
<wire x1="2.1" y1="-1.05" x2="2.45" y2="1.05" width="0.3048" layer="51"/>
<wire x1="2.45" y1="-1.05" x2="2.8" y2="1.05" width="0.3048" layer="51"/>
<wire x1="2.8" y1="-1.05" x2="3.15" y2="1.05" width="0.3048" layer="51"/>
<wire x1="3.15" y1="-1.05" x2="3.5" y2="1.05" width="0.3048" layer="51"/>
<wire x1="3.5" y1="-1.05" x2="3.85" y2="1.4" width="0.3048" layer="51"/>
<pad name="1" x="-3.9" y="-1.35" drill="0.6" shape="octagon"/>
<pad name="2" x="3.9" y="1.35" drill="0.6" shape="octagon"/>
<text x="-4.15" y="1.6251" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.75" y="-2.875" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z15/3">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding counter clockwise</description>
<wire x1="-4.8" y1="-1.25" x2="-2.8" y2="-1.25" width="0.2032" layer="51"/>
<wire x1="-2.8" y1="-1.25" x2="4.8" y2="-1.25" width="0.2032" layer="21"/>
<wire x1="4.8" y1="-1.25" x2="4.8" y2="1.25" width="0.2032" layer="21"/>
<wire x1="4.8" y1="1.25" x2="2.8" y2="1.25" width="0.2032" layer="51"/>
<wire x1="2.8" y1="1.25" x2="-4.8" y2="1.25" width="0.2032" layer="21"/>
<wire x1="-4.8" y1="1.25" x2="-4.8" y2="-1.25" width="0.2032" layer="21"/>
<wire x1="-3.85" y1="-1.4" x2="-3.5" y2="1.05" width="0.254" layer="51"/>
<wire x1="-3.5" y1="-1.05" x2="-3.15" y2="1.05" width="0.254" layer="51"/>
<wire x1="-3.15" y1="-1.05" x2="-2.8" y2="1.05" width="0.254" layer="51"/>
<wire x1="-2.8" y1="-1.05" x2="-2.45" y2="1.05" width="0.254" layer="51"/>
<wire x1="-2.45" y1="-1.05" x2="-2.1" y2="1.05" width="0.254" layer="51"/>
<wire x1="-2.1" y1="-1.05" x2="-1.75" y2="1.05" width="0.254" layer="51"/>
<wire x1="-1.75" y1="-1.05" x2="-1.4" y2="1.05" width="0.254" layer="51"/>
<wire x1="-1.4" y1="-1.05" x2="-1.05" y2="1.05" width="0.254" layer="51"/>
<wire x1="-1.05" y1="-1.05" x2="-0.7" y2="1.05" width="0.254" layer="51"/>
<wire x1="-0.7" y1="-1.05" x2="-0.35" y2="1.05" width="0.254" layer="51"/>
<wire x1="-0.35" y1="-1.05" x2="0" y2="1.05" width="0.254" layer="51"/>
<wire x1="0" y1="-1.05" x2="0.35" y2="1.05" width="0.254" layer="51"/>
<wire x1="0.35" y1="-1.05" x2="0.7" y2="1.05" width="0.254" layer="51"/>
<wire x1="0.7" y1="-1.05" x2="1.05" y2="1.05" width="0.254" layer="51"/>
<wire x1="1.05" y1="-1.05" x2="1.4" y2="1.05" width="0.254" layer="51"/>
<wire x1="1.4" y1="-1.05" x2="1.75" y2="1.05" width="0.254" layer="51"/>
<wire x1="1.75" y1="-1.05" x2="2.1" y2="1.05" width="0.254" layer="51"/>
<wire x1="2.1" y1="-1.05" x2="2.45" y2="1.05" width="0.254" layer="51"/>
<wire x1="2.45" y1="-1.05" x2="2.8" y2="1.05" width="0.254" layer="51"/>
<wire x1="2.8" y1="-1.05" x2="3.15" y2="1.05" width="0.254" layer="51"/>
<wire x1="3.15" y1="-1.05" x2="3.5" y2="1.05" width="0.254" layer="51"/>
<wire x1="3.5" y1="-1.05" x2="3.85" y2="1.4" width="0.254" layer="51"/>
<pad name="1" x="-3.9" y="-1.35" drill="0.6" shape="octagon"/>
<pad name="2" x="3.9" y="1.35" drill="0.6" shape="octagon"/>
<text x="-4.15" y="1.6251" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.75" y="-2.875" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z15/4">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding counter clockwise</description>
<wire x1="-6.6" y1="-1.4" x2="-5" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-5" y1="-1.4" x2="6.6" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="6.6" y1="-1.4" x2="6.6" y2="1.4" width="0.2032" layer="21"/>
<wire x1="6.6" y1="1.4" x2="5" y2="1.4" width="0.2032" layer="51"/>
<wire x1="5" y1="1.4" x2="-6.6" y2="1.4" width="0.2032" layer="21"/>
<wire x1="-6.6" y1="1.4" x2="-6.6" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="-6" y1="-1.8" x2="-5.8" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-5.6" y1="-1.2" x2="-5.4" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-5.2" y1="-1.2" x2="-5" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-4.8" y1="-1.2" x2="-4.6" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-4.4" y1="-1.2" x2="-4.2" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-4" y1="-1.2" x2="-3.8" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-3.6" y1="-1.2" x2="-3.4" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-3.2" y1="-1.2" x2="-3" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-2.8" y1="-1.2" x2="-2.6" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-2.4" y1="-1.2" x2="-2.2" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-2" y1="-1.2" x2="-1.8" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-1.6" y1="-1.2" x2="-1.4" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-1.2" y1="-1.2" x2="-1" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-0.8" y1="-1.2" x2="-0.6" y2="1.2" width="0.3048" layer="51"/>
<wire x1="-0.4" y1="-1.2" x2="-0.2" y2="1.2" width="0.3048" layer="51"/>
<wire x1="0" y1="-1.2" x2="0.2" y2="1.2" width="0.3048" layer="51"/>
<wire x1="0.4" y1="-1.2" x2="0.6" y2="1.2" width="0.3048" layer="51"/>
<wire x1="0.8" y1="-1.2" x2="1" y2="1.2" width="0.3048" layer="51"/>
<wire x1="1.2" y1="-1.2" x2="1.4" y2="1.2" width="0.3048" layer="51"/>
<wire x1="1.6" y1="-1.2" x2="1.8" y2="1.2" width="0.3048" layer="51"/>
<wire x1="2" y1="-1.2" x2="2.2" y2="1.2" width="0.3048" layer="51"/>
<wire x1="2.4" y1="-1.2" x2="2.6" y2="1.2" width="0.3048" layer="51"/>
<wire x1="2.8" y1="-1.2" x2="3" y2="1.2" width="0.3048" layer="51"/>
<wire x1="3.2" y1="-1.2" x2="3.4" y2="1.2" width="0.3048" layer="51"/>
<wire x1="3.6" y1="-1.2" x2="3.8" y2="1.2" width="0.3048" layer="51"/>
<wire x1="4" y1="-1.2" x2="4.2" y2="1.2" width="0.3048" layer="51"/>
<wire x1="4.4" y1="-1.2" x2="4.6" y2="1.2" width="0.3048" layer="51"/>
<wire x1="4.8" y1="-1.2" x2="5" y2="1.2" width="0.3048" layer="51"/>
<wire x1="5.2" y1="-1.2" x2="5.4" y2="1.2" width="0.3048" layer="51"/>
<wire x1="6" y1="1.8" x2="5.6" y2="-1.2" width="0.3048" layer="51"/>
<pad name="1" x="-6" y="-1.8" drill="0.6" shape="octagon"/>
<pad name="2" x="6" y="1.8" drill="0.6" shape="octagon"/>
<text x="-4.15" y="1.6251" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.75" y="-2.875" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z15/56">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding counter clockwise</description>
<wire x1="-6" y1="-1.4" x2="-4.5" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-4.5" y1="-1.4" x2="6" y2="-1.4" width="0.2032" layer="21"/>
<wire x1="6" y1="-1.4" x2="6" y2="0.7" width="0.2032" layer="21"/>
<wire x1="6" y1="0.7" x2="6" y2="1.4" width="0.2032" layer="51"/>
<wire x1="6" y1="1.4" x2="4.5" y2="1.4" width="0.2032" layer="51"/>
<wire x1="4.5" y1="1.4" x2="-6" y2="1.4" width="0.2032" layer="21"/>
<wire x1="-6" y1="1.4" x2="-6" y2="-0.7" width="0.2032" layer="21"/>
<wire x1="-6" y1="-0.7" x2="-6" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-5.55" y1="-1.05" x2="-5.2" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-5.2" y1="-1.05" x2="-4.85" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-4.85" y1="-1.05" x2="-4.5" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-4.5" y1="-1.05" x2="-4.15" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-4.15" y1="-1.05" x2="-3.8" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-3.8" y1="-1.05" x2="-3.45" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-3.45" y1="-1.05" x2="-3.1" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-3.1" y1="-1.05" x2="-2.75" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-2.75" y1="-1.05" x2="-2.4" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-2.4" y1="-1.05" x2="-2.05" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-2.05" y1="-1.05" x2="-1.7" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-1.7" y1="-1.05" x2="-1.35" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-1.35" y1="-1.05" x2="-1" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-1" y1="-1.05" x2="-0.65" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-0.65" y1="-1.05" x2="-0.3" y2="1.05" width="0.3556" layer="51"/>
<wire x1="-0.3" y1="-1.05" x2="0.05" y2="1.05" width="0.3556" layer="51"/>
<wire x1="0.05" y1="-1.05" x2="0.4" y2="1.05" width="0.3556" layer="51"/>
<wire x1="0.4" y1="-1.05" x2="0.75" y2="1.05" width="0.3556" layer="51"/>
<wire x1="0.75" y1="-1.05" x2="1.1" y2="1.05" width="0.3556" layer="51"/>
<wire x1="1.1" y1="-1.05" x2="1.45" y2="1.05" width="0.3556" layer="51"/>
<wire x1="1.45" y1="-1.05" x2="1.8" y2="1.05" width="0.3556" layer="51"/>
<wire x1="1.8" y1="-1.05" x2="2.15" y2="1.05" width="0.3556" layer="51"/>
<wire x1="2.15" y1="-1.05" x2="2.5" y2="1.05" width="0.3556" layer="51"/>
<wire x1="2.5" y1="-1.05" x2="2.85" y2="1.05" width="0.3556" layer="51"/>
<wire x1="2.85" y1="-1.05" x2="3.2" y2="1.05" width="0.3556" layer="51"/>
<wire x1="3.2" y1="-1.05" x2="3.55" y2="1.05" width="0.3556" layer="51"/>
<wire x1="3.55" y1="-1.05" x2="3.9" y2="1.05" width="0.3556" layer="51"/>
<wire x1="3.9" y1="-1.05" x2="4.25" y2="1.05" width="0.3556" layer="51"/>
<wire x1="4.25" y1="-1.05" x2="4.6" y2="1.05" width="0.3556" layer="51"/>
<wire x1="4.6" y1="-1.05" x2="4.95" y2="1.05" width="0.3556" layer="51"/>
<wire x1="4.95" y1="-1.05" x2="5.3" y2="1.05" width="0.3556" layer="51"/>
<pad name="1" x="-5.5" y="-1.3" drill="0.6" shape="octagon"/>
<pad name="2" x="5.5" y="1.3" drill="0.6" shape="octagon"/>
<text x="-5.723" y="1.717" size="1.27" layer="25">&gt;NAME</text>
<text x="-4.707" y="-2.967" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z4/8">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding clockwise</description>
<wire x1="9.9" y1="-2.85" x2="8.85" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="8.85" y1="-2.85" x2="5.9" y2="-2.85" width="0.2032" layer="51"/>
<wire x1="5.9" y1="-2.85" x2="-9.9" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="-9.9" y1="-2.85" x2="-9.9" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-9.9" y1="2.85" x2="-8.85" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-8.85" y1="2.85" x2="-5.9" y2="2.85" width="0.2032" layer="51"/>
<wire x1="-5.9" y1="2.85" x2="9.9" y2="2.85" width="0.2032" layer="21"/>
<wire x1="9.9" y1="2.85" x2="9.9" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="7.5" y1="-3" x2="6.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="6.9" y1="-2.7" x2="6.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="6.3" y1="-2.7" x2="5.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="5.7" y1="-2.7" x2="5.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="5.1" y1="-2.7" x2="4.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="4.5" y1="-2.7" x2="3.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="3.9" y1="-2.7" x2="3.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="3.3" y1="-2.7" x2="2.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="2.7" y1="-2.7" x2="2.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="2.1" y1="-2.7" x2="1.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="1.5" y1="-2.7" x2="0.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="0.9" y1="-2.7" x2="0.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="0.3" y1="-2.7" x2="-0.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="-0.3" y1="-2.7" x2="-0.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="-0.9" y1="-2.7" x2="-1.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="-1.5" y1="-2.7" x2="-2.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="-2.1" y1="-2.7" x2="-2.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="-2.7" y1="-2.7" x2="-3.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="-3.3" y1="-2.7" x2="-3.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="-3.9" y1="-2.7" x2="-4.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="-4.5" y1="-2.7" x2="-5.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="-5.1" y1="-2.7" x2="-5.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="-5.7" y1="-2.7" x2="-6.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="-6.3" y1="-2.7" x2="-6.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="-6.9" y1="-2.7" x2="-7.5" y2="3" width="0.508" layer="51"/>
<pad name="1" x="7.4" y="-2.95" drill="0.8" shape="octagon"/>
<pad name="2" x="-7.4" y="2.95" drill="0.8" shape="octagon"/>
<text x="-5.55" y="3.175" size="1.27" layer="25">&gt;NAME</text>
<text x="-9.6" y="-4.4249" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z28S/2">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding clockwise</description>
<wire x1="5.65" y1="-2.2" x2="3.6" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="3.6" y1="-2.2" x2="1.6" y2="-2.2" width="0.2032" layer="51"/>
<wire x1="1.6" y1="-2.2" x2="-5.65" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-5.65" y1="-2.2" x2="-5.65" y2="2.2" width="0.2032" layer="21"/>
<wire x1="-5.65" y1="2.2" x2="-3.6" y2="2.2" width="0.2032" layer="21"/>
<wire x1="-3.6" y1="2.2" x2="-1.6" y2="2.2" width="0.2032" layer="51"/>
<wire x1="-1.6" y1="2.2" x2="5.65" y2="2.2" width="0.2032" layer="21"/>
<wire x1="5.65" y1="2.2" x2="5.65" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="2" x2="-2.4" y2="-2" width="0.3556" layer="51"/>
<wire x1="-2.2" y1="2" x2="-2" y2="-2" width="0.3556" layer="51"/>
<wire x1="-1.8" y1="2" x2="-1.6" y2="-2" width="0.3556" layer="51"/>
<wire x1="-1.4" y1="2" x2="-1.2" y2="-2" width="0.3556" layer="51"/>
<wire x1="-1" y1="2" x2="-0.8" y2="-2" width="0.3556" layer="51"/>
<wire x1="-0.6" y1="2" x2="-0.4" y2="-2" width="0.3556" layer="51"/>
<wire x1="-0.2" y1="2" x2="0" y2="-2" width="0.3556" layer="51"/>
<wire x1="0.2" y1="2" x2="0.4" y2="-2" width="0.3556" layer="51"/>
<wire x1="0.6" y1="2" x2="0.8" y2="-2" width="0.3556" layer="51"/>
<wire x1="1" y1="2" x2="1.2" y2="-2" width="0.3556" layer="51"/>
<wire x1="1.4" y1="2" x2="1.6" y2="-2" width="0.3556" layer="51"/>
<wire x1="1.8" y1="2" x2="2" y2="-2" width="0.3556" layer="51"/>
<wire x1="2.2" y1="2" x2="2.4" y2="-2" width="0.3556" layer="51"/>
<pad name="1" x="2.6" y="-2.1" drill="0.6" shape="octagon"/>
<pad name="2" x="-2.6" y="2.1" drill="0.6" shape="octagon"/>
<text x="-1.703" y="2.6439" size="1.27" layer="25">&gt;NAME</text>
<text x="-4.624" y="-3.7671" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z4/22">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding clockwise</description>
<wire x1="3.3" y1="-2.1" x2="3" y2="2.1" width="0.508" layer="51"/>
<wire x1="2.7" y1="-2.1" x2="2.4" y2="2.1" width="0.508" layer="51"/>
<wire x1="2.1" y1="-2.1" x2="1.8" y2="2.1" width="0.508" layer="51"/>
<wire x1="1.5" y1="-2.1" x2="1.2" y2="2.1" width="0.508" layer="51"/>
<wire x1="0.9" y1="-2.1" x2="0.6" y2="2.1" width="0.508" layer="51"/>
<wire x1="0.3" y1="-2.1" x2="0" y2="2.1" width="0.508" layer="51"/>
<wire x1="-0.3" y1="-2.1" x2="-0.6" y2="2.1" width="0.508" layer="51"/>
<wire x1="-0.9" y1="-2.1" x2="-1.2" y2="2.1" width="0.508" layer="51"/>
<wire x1="-1.5" y1="-2.1" x2="-1.8" y2="2.1" width="0.508" layer="51"/>
<wire x1="-2.1" y1="-2.1" x2="-2.4" y2="2.1" width="0.508" layer="51"/>
<wire x1="-2.7" y1="-2.1" x2="-3" y2="2.1" width="0.508" layer="51"/>
<wire x1="-3.3" y1="-2.1" x2="-3.6" y2="2.1" width="0.508" layer="51"/>
<wire x1="7.4" y1="-2.35" x2="4.5" y2="-2.35" width="0.2032" layer="21"/>
<wire x1="4.5" y1="-2.35" x2="2.4" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-2.35" x2="-7.4" y2="-2.35" width="0.2032" layer="21"/>
<wire x1="-7.4" y1="-2.35" x2="-7.4" y2="2.35" width="0.2032" layer="21"/>
<wire x1="-7.4" y1="2.35" x2="-4.5" y2="2.35" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="2.35" x2="-2.4" y2="2.35" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="2.35" x2="7.4" y2="2.35" width="0.2032" layer="21"/>
<wire x1="7.4" y1="2.35" x2="7.4" y2="-2.35" width="0.2032" layer="21"/>
<pad name="1" x="3.5" y="-2.45" drill="0.7" shape="octagon"/>
<pad name="2" x="-3.5" y="2.45" drill="0.7" shape="octagon"/>
<text x="-2.463" y="2.6439" size="1.27" layer="25">&gt;NAME</text>
<text x="-6.864" y="-4.0211" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z27/24">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding clockwise</description>
<wire x1="8.15" y1="-1.7" x2="6.125" y2="-1.7" width="0.2032" layer="51"/>
<wire x1="6.125" y1="-1.7" x2="-8.15" y2="-1.7" width="0.2032" layer="21"/>
<wire x1="-8.15" y1="-1.7" x2="-8.15" y2="1.7" width="0.2032" layer="21"/>
<wire x1="-8.15" y1="1.7" x2="-6.3" y2="1.7" width="0.2032" layer="51"/>
<wire x1="-6.3" y1="1.7" x2="8.15" y2="1.7" width="0.2032" layer="21"/>
<wire x1="8.15" y1="1.7" x2="8.15" y2="-1.7" width="0.2032" layer="21"/>
<wire x1="7.175" y1="-1.925" x2="6.825" y2="1.575" width="0.3048" layer="51"/>
<wire x1="6.475" y1="1.575" x2="6.825" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="6.125" y1="1.575" x2="6.475" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="5.775" y1="1.575" x2="6.125" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="5.425" y1="1.575" x2="5.775" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="5.075" y1="1.575" x2="5.425" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="4.725" y1="1.575" x2="5.075" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="4.375" y1="1.575" x2="4.725" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="4.025" y1="1.575" x2="4.375" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="3.675" y1="1.575" x2="4.025" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="3.325" y1="1.575" x2="3.675" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="2.975" y1="1.575" x2="3.325" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="2.625" y1="1.575" x2="2.975" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="2.275" y1="1.575" x2="2.625" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="1.925" y1="1.575" x2="2.275" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="1.575" y1="1.575" x2="1.925" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="1.225" y1="1.575" x2="1.5751" y2="-1.5751" width="0.3048" layer="51"/>
<wire x1="0.875" y1="1.575" x2="1.225" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="0.525" y1="1.575" x2="0.875" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="0.175" y1="1.575" x2="0.525" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-0.175" y1="1.575" x2="0.175" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-0.525" y1="1.575" x2="-0.175" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-0.875" y1="1.575" x2="-0.525" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-1.225" y1="1.575" x2="-0.875" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-1.5751" y1="1.5751" x2="-1.225" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-1.925" y1="1.575" x2="-1.575" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-2.275" y1="1.575" x2="-1.925" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-2.625" y1="1.575" x2="-2.275" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-2.975" y1="1.575" x2="-2.625" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-3.325" y1="1.575" x2="-2.975" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-3.675" y1="1.575" x2="-3.325" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-4.025" y1="1.575" x2="-3.675" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-4.375" y1="1.575" x2="-4.025" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-4.725" y1="1.575" x2="-4.375" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-5.075" y1="1.575" x2="-4.725" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-5.425" y1="1.575" x2="-5.075" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-5.775" y1="1.575" x2="-5.425" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-6.125" y1="1.575" x2="-5.775" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-6.475" y1="1.575" x2="-6.125" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-6.825" y1="1.575" x2="-6.475" y2="-1.575" width="0.3048" layer="51"/>
<wire x1="-7.175" y1="1.925" x2="-6.825" y2="-1.575" width="0.3048" layer="51"/>
<pad name="1" x="7.2" y="-1.9" drill="0.7" shape="octagon"/>
<pad name="2" x="-7.2" y="1.9" drill="0.7" shape="octagon"/>
<text x="-6.05" y="1.9751" size="1.27" layer="25">&gt;NAME</text>
<text x="-5.2" y="-3.225" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z4/47">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding clockwise</description>
<wire x1="9.9" y1="-2.3" x2="5.4" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="5.4" y1="-2.3" x2="3.6" y2="-2.3" width="0.2032" layer="51"/>
<wire x1="3.6" y1="-2.3" x2="-9.9" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="-9.9" y1="-2.3" x2="-9.9" y2="2.3" width="0.2032" layer="21"/>
<wire x1="-9.9" y1="2.3" x2="-5.4" y2="2.3" width="0.2032" layer="21"/>
<wire x1="-5.4" y1="2.3" x2="-3.6" y2="2.3" width="0.2032" layer="51"/>
<wire x1="-3.6" y1="2.3" x2="9.9" y2="2.3" width="0.2032" layer="21"/>
<wire x1="9.9" y1="2.3" x2="9.9" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="4.5" y1="-2.4" x2="4.2" y2="2.1" width="0.508" layer="51"/>
<wire x1="3.9" y1="-2.1" x2="3.6" y2="2.1" width="0.508" layer="51"/>
<wire x1="3.3" y1="-2.1" x2="3" y2="2.1" width="0.508" layer="51"/>
<wire x1="2.7" y1="-2.1" x2="2.4" y2="2.1" width="0.508" layer="51"/>
<wire x1="2.1" y1="-2.1" x2="1.8" y2="2.1" width="0.508" layer="51"/>
<wire x1="1.5" y1="-2.1" x2="1.2" y2="2.1" width="0.508" layer="51"/>
<wire x1="0.9" y1="-2.1" x2="0.6" y2="2.1" width="0.508" layer="51"/>
<wire x1="0.3" y1="-2.1" x2="0" y2="2.1" width="0.508" layer="51"/>
<wire x1="-0.3" y1="-2.1" x2="-0.6" y2="2.1" width="0.508" layer="51"/>
<wire x1="-0.9" y1="-2.1" x2="-1.2" y2="2.1" width="0.508" layer="51"/>
<wire x1="-1.5" y1="-2.1" x2="-1.8" y2="2.1" width="0.508" layer="51"/>
<wire x1="-2.1" y1="-2.1" x2="-2.4" y2="2.1" width="0.508" layer="51"/>
<wire x1="-2.7" y1="-2.1" x2="-3" y2="2.1" width="0.508" layer="51"/>
<wire x1="-3.3" y1="-2.1" x2="-3.6" y2="2.1" width="0.508" layer="51"/>
<wire x1="-3.9" y1="-2.1" x2="-4.5" y2="2.4" width="0.508" layer="51"/>
<pad name="1" x="4.5" y="-2.4" drill="0.7" shape="octagon"/>
<pad name="2" x="-4.5" y="2.4" drill="0.7" shape="octagon"/>
<text x="-3.3" y="2.5751" size="1.27" layer="25">&gt;NAME</text>
<text x="-9.6" y="-3.875" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z4/55">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding clockwise</description>
<wire x1="9.9" y1="-2.3" x2="6.15" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="4.1" y1="-2.3" x2="-9.9" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="-9.9" y1="-2.3" x2="-9.9" y2="2.3" width="0.2032" layer="21"/>
<wire x1="-9.9" y1="2.3" x2="-6.15" y2="2.3" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="2.3" x2="9.9" y2="2.3" width="0.2032" layer="21"/>
<wire x1="9.9" y1="2.3" x2="9.9" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="5.1" y1="-2.4" x2="4.8" y2="2.1" width="0.508" layer="51"/>
<wire x1="4.5" y1="-2.1" x2="4.2" y2="2.1" width="0.508" layer="51"/>
<wire x1="3.9" y1="-2.1" x2="3.6" y2="2.1" width="0.508" layer="51"/>
<wire x1="3.3" y1="-2.1" x2="3" y2="2.1" width="0.508" layer="51"/>
<wire x1="2.7" y1="-2.1" x2="2.4" y2="2.1" width="0.508" layer="51"/>
<wire x1="2.1" y1="-2.1" x2="1.8" y2="2.1" width="0.508" layer="51"/>
<wire x1="1.5" y1="-2.1" x2="1.2" y2="2.1" width="0.508" layer="51"/>
<wire x1="0.9" y1="-2.1" x2="0.6" y2="2.1" width="0.508" layer="51"/>
<wire x1="0.3" y1="-2.1" x2="0" y2="2.1" width="0.508" layer="51"/>
<wire x1="-0.3" y1="-2.1" x2="-0.6" y2="2.1" width="0.508" layer="51"/>
<wire x1="-0.9" y1="-2.1" x2="-1.2" y2="2.1" width="0.508" layer="51"/>
<wire x1="-1.5" y1="-2.1" x2="-1.8" y2="2.1" width="0.508" layer="51"/>
<wire x1="-2.1" y1="-2.1" x2="-2.4" y2="2.1" width="0.508" layer="51"/>
<wire x1="-2.7" y1="-2.1" x2="-3" y2="2.1" width="0.508" layer="51"/>
<wire x1="-4.5" y1="-2.1" x2="-5.1" y2="2.4" width="0.508" layer="51"/>
<wire x1="-3.3" y1="-2.1" x2="-3.6" y2="2.1" width="0.508" layer="51"/>
<wire x1="-3.9" y1="-2.1" x2="-4.2" y2="2.1" width="0.508" layer="51"/>
<wire x1="6.15" y1="-2.3" x2="4.15" y2="-2.3" width="0.2032" layer="51"/>
<wire x1="-6.15" y1="2.3" x2="-4.15" y2="2.3" width="0.2032" layer="51"/>
<pad name="1" x="5.1" y="-2.4" drill="0.7" shape="octagon"/>
<pad name="2" x="-5.1" y="2.4" drill="0.7" shape="octagon"/>
<text x="-3.8" y="2.5751" size="1.27" layer="25">&gt;NAME</text>
<text x="-9.65" y="-3.825" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z28/7">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding clockwise</description>
<wire x1="4.9" y1="-1.75" x2="3" y2="-1.75" width="0.2032" layer="51"/>
<wire x1="3" y1="-1.75" x2="-4.9" y2="-1.75" width="0.2032" layer="21"/>
<wire x1="-4.9" y1="-1.75" x2="-4.9" y2="1.75" width="0.2032" layer="21"/>
<wire x1="-4.9" y1="1.75" x2="-3" y2="1.75" width="0.2032" layer="51"/>
<wire x1="-3" y1="1.75" x2="4.9" y2="1.75" width="0.2032" layer="21"/>
<wire x1="4.9" y1="1.75" x2="4.9" y2="-1.75" width="0.2032" layer="21"/>
<wire x1="4.05" y1="-1.95" x2="3.75" y2="1.65" width="0.254" layer="51"/>
<wire x1="3.75" y1="-1.65" x2="3.45" y2="1.65" width="0.254" layer="51"/>
<wire x1="3.45" y1="-1.65" x2="3.15" y2="1.65" width="0.254" layer="51"/>
<wire x1="3.15" y1="-1.65" x2="2.85" y2="1.65" width="0.254" layer="51"/>
<wire x1="2.85" y1="-1.65" x2="2.55" y2="1.65" width="0.254" layer="51"/>
<wire x1="2.55" y1="-1.65" x2="2.25" y2="1.65" width="0.254" layer="51"/>
<wire x1="2.25" y1="-1.65" x2="1.95" y2="1.65" width="0.254" layer="51"/>
<wire x1="1.95" y1="-1.65" x2="1.65" y2="1.65" width="0.254" layer="51"/>
<wire x1="1.65" y1="-1.65" x2="1.35" y2="1.65" width="0.254" layer="51"/>
<wire x1="1.35" y1="-1.65" x2="1.05" y2="1.65" width="0.254" layer="51"/>
<wire x1="1.05" y1="-1.65" x2="0.75" y2="1.65" width="0.254" layer="51"/>
<wire x1="0.75" y1="-1.65" x2="0.45" y2="1.65" width="0.254" layer="51"/>
<wire x1="0.45" y1="-1.65" x2="0.15" y2="1.65" width="0.254" layer="51"/>
<wire x1="0.15" y1="-1.65" x2="-0.15" y2="1.65" width="0.254" layer="51"/>
<wire x1="-0.15" y1="-1.65" x2="-0.45" y2="1.65" width="0.254" layer="51"/>
<wire x1="-0.45" y1="-1.65" x2="-0.75" y2="1.65" width="0.254" layer="51"/>
<wire x1="-0.75" y1="-1.65" x2="-1.05" y2="1.65" width="0.254" layer="51"/>
<wire x1="-1.05" y1="-1.65" x2="-1.35" y2="1.65" width="0.254" layer="51"/>
<wire x1="-1.35" y1="-1.65" x2="-1.65" y2="1.65" width="0.254" layer="51"/>
<wire x1="-1.65" y1="-1.65" x2="-1.95" y2="1.65" width="0.254" layer="51"/>
<wire x1="-1.95" y1="-1.65" x2="-2.25" y2="1.65" width="0.254" layer="51"/>
<wire x1="-2.25" y1="-1.65" x2="-2.55" y2="1.65" width="0.254" layer="51"/>
<wire x1="-2.55" y1="-1.65" x2="-2.85" y2="1.65" width="0.254" layer="51"/>
<wire x1="-2.85" y1="-1.65" x2="-3.15" y2="1.65" width="0.254" layer="51"/>
<wire x1="-3.15" y1="-1.65" x2="-3.45" y2="1.65" width="0.254" layer="51"/>
<wire x1="-3.45" y1="-1.65" x2="-3.75" y2="1.65" width="0.254" layer="51"/>
<wire x1="-3.75" y1="-1.65" x2="-4.05" y2="1.95" width="0.254" layer="51"/>
<pad name="1" x="4" y="-1.85" drill="0.6" shape="octagon"/>
<pad name="2" x="-4" y="1.85" drill="0.6" shape="octagon"/>
<text x="-2.6" y="2.0249" size="1.27" layer="25">&gt;NAME</text>
<text x="-4.8" y="-3.2751" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z4/10">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding clockwise</description>
<wire x1="9.9" y1="-2.85" x2="8.85" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="8.85" y1="-2.85" x2="5.9" y2="-2.85" width="0.2032" layer="51"/>
<wire x1="5.9" y1="-2.85" x2="-9.9" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="-9.9" y1="-2.85" x2="-9.9" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-9.9" y1="2.85" x2="-8.85" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-8.85" y1="2.85" x2="-5.9" y2="2.85" width="0.2032" layer="51"/>
<wire x1="-5.9" y1="2.85" x2="9.9" y2="2.85" width="0.2032" layer="21"/>
<wire x1="9.9" y1="2.85" x2="9.9" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="7.5" y1="-3" x2="6.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="6.9" y1="-2.7" x2="6.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="6.3" y1="-2.7" x2="5.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="5.7" y1="-2.7" x2="5.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="5.1" y1="-2.7" x2="4.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="4.5" y1="-2.7" x2="3.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="3.9" y1="-2.7" x2="3.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="3.3" y1="-2.7" x2="2.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="2.7" y1="-2.7" x2="2.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="2.1" y1="-2.7" x2="1.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="1.5" y1="-2.7" x2="0.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="0.9" y1="-2.7" x2="0.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="0.3" y1="-2.7" x2="-0.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="-0.3" y1="-2.7" x2="-0.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="-0.9" y1="-2.7" x2="-1.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="-1.5" y1="-2.7" x2="-2.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="-2.1" y1="-2.7" x2="-2.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="-2.7" y1="-2.7" x2="-3.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="-3.3" y1="-2.7" x2="-3.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="-3.9" y1="-2.7" x2="-4.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="-4.5" y1="-2.7" x2="-5.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="-5.1" y1="-2.7" x2="-5.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="-5.7" y1="-2.7" x2="-6.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="-6.3" y1="-2.7" x2="-6.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="-6.9" y1="-2.7" x2="-7.5" y2="3" width="0.508" layer="51"/>
<pad name="1" x="7.5" y="-2.95" drill="0.8" shape="octagon"/>
<pad name="2" x="-7.5" y="2.95" drill="0.8" shape="octagon"/>
<text x="-6.411" y="3.2979" size="1.27" layer="25">&gt;NAME</text>
<text x="-6.354" y="-4.5481" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z4/15">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding clockwise</description>
<wire x1="9.9" y1="-2.85" x2="8.85" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="8.85" y1="-2.85" x2="5.9" y2="-2.85" width="0.2032" layer="51"/>
<wire x1="5.9" y1="-2.85" x2="-9.9" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="-9.9" y1="-2.85" x2="-9.9" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-9.9" y1="2.85" x2="-8.85" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-8.85" y1="2.85" x2="-5.9" y2="2.85" width="0.2032" layer="51"/>
<wire x1="-5.9" y1="2.85" x2="9.9" y2="2.85" width="0.2032" layer="21"/>
<wire x1="9.9" y1="2.85" x2="9.9" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="7.1" y1="-3" x2="6.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="6.5" y1="-2.7" x2="5.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="5.9" y1="-2.7" x2="5.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="5.3" y1="-2.7" x2="4.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="4.7" y1="-2.7" x2="4.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="4.1" y1="-2.7" x2="3.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="3.5" y1="-2.7" x2="2.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="2.9" y1="-2.7" x2="2.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="2.3" y1="-2.7" x2="1.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="1.7" y1="-2.7" x2="1.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="1.1" y1="-2.7" x2="0.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="0.7" y1="-2.7" x2="0.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="0.1" y1="-2.7" x2="-0.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="-0.5" y1="-2.7" x2="-1.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="-1.1" y1="-2.7" x2="-1.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="-1.7" y1="-2.7" x2="-2.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="-2.3" y1="-2.7" x2="-2.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="-2.9" y1="-2.7" x2="-3.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="-3.5" y1="-2.7" x2="-4.1" y2="2.7" width="0.508" layer="51"/>
<wire x1="-4.1" y1="-2.7" x2="-4.7" y2="2.7" width="0.508" layer="51"/>
<wire x1="-4.7" y1="-2.7" x2="-5.3" y2="2.7" width="0.508" layer="51"/>
<wire x1="-5.3" y1="-2.7" x2="-5.9" y2="2.7" width="0.508" layer="51"/>
<wire x1="-5.9" y1="-2.7" x2="-6.5" y2="2.7" width="0.508" layer="51"/>
<wire x1="-6.5" y1="-2.7" x2="-7.1" y2="3" width="0.508" layer="51"/>
<pad name="1" x="7.1" y="-2.95" drill="0.8" shape="octagon"/>
<pad name="2" x="-7.1" y="2.95" drill="0.8" shape="octagon"/>
<text x="-5.05" y="3.175" size="1.27" layer="25">&gt;NAME</text>
<text x="-9.6" y="-4.4249" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z4/25">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding clockwise</description>
<wire x1="9.75" y1="-2.85" x2="7.4" y2="-2.85" width="0.2032" layer="51"/>
<wire x1="7.4" y1="-2.85" x2="-12.4" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="-12.4" y1="-2.85" x2="-12.4" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-9.75" y1="2.85" x2="-7.4" y2="2.85" width="0.2032" layer="51"/>
<wire x1="-7.4" y1="2.85" x2="12.4" y2="2.85" width="0.2032" layer="21"/>
<wire x1="12.4" y1="2.85" x2="12.4" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="8.6" y1="-3" x2="8" y2="2.7" width="0.508" layer="51"/>
<wire x1="8" y1="-2.7" x2="7.4" y2="2.7" width="0.508" layer="51"/>
<wire x1="7.4" y1="-2.7" x2="6.8" y2="2.7" width="0.508" layer="51"/>
<wire x1="6.8" y1="-2.7" x2="6.2" y2="2.7" width="0.508" layer="51"/>
<wire x1="6.2" y1="-2.7" x2="5.6" y2="2.7" width="0.508" layer="51"/>
<wire x1="5.6" y1="-2.7" x2="5" y2="2.7" width="0.508" layer="51"/>
<wire x1="5" y1="-2.7" x2="4.4" y2="2.7" width="0.508" layer="51"/>
<wire x1="4.4" y1="-2.7" x2="3.8" y2="2.7" width="0.508" layer="51"/>
<wire x1="3.8" y1="-2.7" x2="3.2" y2="2.7" width="0.508" layer="51"/>
<wire x1="3.2" y1="-2.7" x2="2.6" y2="2.7" width="0.508" layer="51"/>
<wire x1="2.6" y1="-2.7" x2="2" y2="2.7" width="0.508" layer="51"/>
<wire x1="-0.8" y1="-2.7" x2="-1.4" y2="2.7" width="0.508" layer="51"/>
<wire x1="-1.4" y1="-2.7" x2="-2" y2="2.7" width="0.508" layer="51"/>
<wire x1="-2" y1="-2.7" x2="-2.6" y2="2.7" width="0.508" layer="51"/>
<wire x1="-2.6" y1="-2.7" x2="-3.2" y2="2.7" width="0.508" layer="51"/>
<wire x1="-3.2" y1="-2.7" x2="-3.8" y2="2.7" width="0.508" layer="51"/>
<wire x1="-3.8" y1="-2.7" x2="-4.4" y2="2.7" width="0.508" layer="51"/>
<wire x1="-4.4" y1="-2.7" x2="-5" y2="2.7" width="0.508" layer="51"/>
<wire x1="-5" y1="-2.7" x2="-5.6" y2="2.7" width="0.508" layer="51"/>
<wire x1="-5.6" y1="-2.7" x2="-6.2" y2="2.7" width="0.508" layer="51"/>
<wire x1="-6.2" y1="-2.7" x2="-6.8" y2="2.7" width="0.508" layer="51"/>
<wire x1="-6.8" y1="-2.7" x2="-7.4" y2="2.7" width="0.508" layer="51"/>
<wire x1="-7.4" y1="-2.7" x2="-8" y2="2.7" width="0.508" layer="51"/>
<wire x1="-8" y1="-2.7" x2="-8.6" y2="3" width="0.508" layer="51"/>
<wire x1="2" y1="-2.7" x2="1.4" y2="2.7" width="0.508" layer="51"/>
<wire x1="1.4" y1="-2.7" x2="0.8" y2="2.7" width="0.508" layer="51"/>
<wire x1="0.8" y1="-2.7" x2="0.2" y2="2.7" width="0.508" layer="51"/>
<wire x1="0.2" y1="-2.7" x2="-0.4" y2="2.7" width="0.508" layer="51"/>
<wire x1="-0.4" y1="-2.7" x2="-1" y2="2.7" width="0.508" layer="51"/>
<wire x1="12.4" y1="-2.85" x2="9.6" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="-12.4" y1="2.85" x2="-9.6" y2="2.85" width="0.2032" layer="21"/>
<pad name="1" x="8.6" y="-2.95" drill="0.8" shape="octagon"/>
<pad name="2" x="-8.6" y="2.95" drill="0.8" shape="octagon"/>
<text x="-6.8" y="3.175" size="1.27" layer="25">&gt;NAME</text>
<text x="-12.35" y="-4.4249" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="Z4/28">
<description>FREE-SUSPENSION &lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
type Z, winding clockwise</description>
<wire x1="10.5" y1="-2.85" x2="8.15" y2="-2.85" width="0.2032" layer="51"/>
<wire x1="8.15" y1="-2.85" x2="-12.4" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="-12.4" y1="-2.85" x2="-12.4" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-10.5" y1="2.85" x2="-8.15" y2="2.85" width="0.2032" layer="51"/>
<wire x1="-8.15" y1="2.85" x2="12.4" y2="2.85" width="0.2032" layer="21"/>
<wire x1="12.4" y1="2.85" x2="12.4" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="9.35" y1="-3" x2="8.75" y2="2.7" width="0.508" layer="51"/>
<wire x1="8.75" y1="-2.7" x2="8.15" y2="2.7" width="0.508" layer="51"/>
<wire x1="8.15" y1="-2.7" x2="7.55" y2="2.7" width="0.508" layer="51"/>
<wire x1="7.55" y1="-2.7" x2="6.95" y2="2.7" width="0.508" layer="51"/>
<wire x1="6.95" y1="-2.7" x2="6.35" y2="2.7" width="0.508" layer="51"/>
<wire x1="6.35" y1="-2.7" x2="5.75" y2="2.7" width="0.508" layer="51"/>
<wire x1="5.75" y1="-2.7" x2="5.15" y2="2.7" width="0.508" layer="51"/>
<wire x1="5.15" y1="-2.7" x2="4.55" y2="2.7" width="0.508" layer="51"/>
<wire x1="4.55" y1="-2.7" x2="3.95" y2="2.7" width="0.508" layer="51"/>
<wire x1="3.95" y1="-2.7" x2="3.35" y2="2.7" width="0.508" layer="51"/>
<wire x1="3.35" y1="-2.7" x2="2.75" y2="2.7" width="0.508" layer="51"/>
<wire x1="-1.55" y1="-2.7" x2="-2.15" y2="2.7" width="0.508" layer="51"/>
<wire x1="-2.15" y1="-2.7" x2="-2.75" y2="2.7" width="0.508" layer="51"/>
<wire x1="-2.75" y1="-2.7" x2="-3.35" y2="2.7" width="0.508" layer="51"/>
<wire x1="-3.35" y1="-2.7" x2="-3.95" y2="2.7" width="0.508" layer="51"/>
<wire x1="-3.95" y1="-2.7" x2="-4.55" y2="2.7" width="0.508" layer="51"/>
<wire x1="-4.55" y1="-2.7" x2="-5.15" y2="2.7" width="0.508" layer="51"/>
<wire x1="-5.15" y1="-2.7" x2="-5.75" y2="2.7" width="0.508" layer="51"/>
<wire x1="-5.75" y1="-2.7" x2="-6.35" y2="2.7" width="0.508" layer="51"/>
<wire x1="-6.35" y1="-2.7" x2="-6.95" y2="2.7" width="0.508" layer="51"/>
<wire x1="-6.95" y1="-2.7" x2="-7.55" y2="2.7" width="0.508" layer="51"/>
<wire x1="-7.55" y1="-2.7" x2="-8.15" y2="2.7" width="0.508" layer="51"/>
<wire x1="-8.15" y1="-2.7" x2="-8.75" y2="2.7" width="0.508" layer="51"/>
<wire x1="-8.75" y1="-2.7" x2="-9.35" y2="3" width="0.508" layer="51"/>
<wire x1="2.75" y1="-2.7" x2="2.15" y2="2.7" width="0.508" layer="51"/>
<wire x1="2.15" y1="-2.7" x2="1.55" y2="2.7" width="0.508" layer="51"/>
<wire x1="1.55" y1="-2.7" x2="0.95" y2="2.7" width="0.508" layer="51"/>
<wire x1="0.95" y1="-2.7" x2="0.35" y2="2.7" width="0.508" layer="51"/>
<wire x1="0.35" y1="-2.7" x2="-0.25" y2="2.7" width="0.508" layer="51"/>
<wire x1="12.4" y1="-2.85" x2="10.35" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="-12.4" y1="2.85" x2="-10.35" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-0.95" y1="-2.7" x2="-1.55" y2="2.7" width="0.508" layer="51"/>
<wire x1="-0.35" y1="-2.7" x2="-0.95" y2="2.7" width="0.508" layer="51"/>
<pad name="1" x="9.35" y="-2.95" drill="0.8" shape="octagon"/>
<pad name="2" x="-9.35" y="2.95" drill="0.8" shape="octagon"/>
<text x="-7.8" y="3.175" size="1.27" layer="25">&gt;NAME</text>
<text x="-12.1" y="-4.4249" size="1.27" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="L-ZL">
<wire x1="4.064" y1="2.032" x2="4.572" y2="2.032" width="0.254" layer="94" curve="-126.869898" cap="flat"/>
<wire x1="2.54" y1="2.032" x2="3.048" y2="2.032" width="0.254" layer="94" curve="-126.869898" cap="flat"/>
<wire x1="1.016" y1="2.032" x2="1.524" y2="2.032" width="0.254" layer="94" curve="-126.869898" cap="flat"/>
<wire x1="-0.508" y1="2.032" x2="0" y2="2.032" width="0.254" layer="94" curve="-126.869898" cap="flat"/>
<wire x1="-2.032" y1="2.032" x2="-1.524" y2="2.032" width="0.254" layer="94" curve="-126.869898" cap="flat"/>
<wire x1="-2.032" y1="2.032" x2="0" y2="2.032" width="0.254" layer="94" curve="253.739795" cap="flat"/>
<wire x1="-0.508" y1="2.032" x2="1.524" y2="2.032" width="0.254" layer="94" curve="253.739795" cap="flat"/>
<wire x1="-2.54" y1="0" x2="-1.524" y2="2.032" width="0.254" layer="94" curve="126.869898" cap="flat"/>
<wire x1="1.016" y1="2.032" x2="3.048" y2="2.032" width="0.254" layer="94" curve="253.739795" cap="flat"/>
<wire x1="2.54" y1="2.032" x2="4.572" y2="2.032" width="0.254" layer="94" curve="253.739795" cap="flat"/>
<wire x1="4.064" y1="2.032" x2="5.08" y2="0" width="0.254" layer="94" curve="126.869898" cap="flat"/>
<wire x1="-2.794" y1="-0.762" x2="-1.778" y2="-0.762" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-0.762" x2="0" y2="-0.762" width="0.254" layer="94"/>
<wire x1="0.762" y1="-0.762" x2="1.778" y2="-0.762" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.762" x2="3.556" y2="-0.762" width="0.254" layer="94"/>
<wire x1="4.318" y1="-0.762" x2="5.334" y2="-0.762" width="0.254" layer="94"/>
<text x="-4.88" y="2.794" size="1.778" layer="95">&gt;NAME</text>
<text x="-4.88" y="-3.048" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="7.62" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
<symbol name="L-ZR">
<wire x1="-2.032" y1="-2.032" x2="-1.524" y2="-2.032" width="0.254" layer="94" curve="126.869898" cap="flat"/>
<wire x1="-0.508" y1="-2.032" x2="0" y2="-2.032" width="0.254" layer="94" curve="126.869898" cap="flat"/>
<wire x1="1.016" y1="-2.032" x2="1.524" y2="-2.032" width="0.254" layer="94" curve="126.869898" cap="flat"/>
<wire x1="2.54" y1="-2.032" x2="3.048" y2="-2.032" width="0.254" layer="94" curve="126.869898" cap="flat"/>
<wire x1="4.064" y1="-2.032" x2="4.572" y2="-2.032" width="0.254" layer="94" curve="126.869898" cap="flat"/>
<wire x1="2.54" y1="-2.032" x2="4.572" y2="-2.032" width="0.254" layer="94" curve="-253.739795" cap="flat"/>
<wire x1="1.016" y1="-2.032" x2="3.048" y2="-2.032" width="0.254" layer="94" curve="-253.739795" cap="flat"/>
<wire x1="4.064" y1="-2.032" x2="5.08" y2="0" width="0.254" layer="94" curve="-126.869898" cap="flat"/>
<wire x1="-0.508" y1="-2.032" x2="1.524" y2="-2.032" width="0.254" layer="94" curve="-253.739795" cap="flat"/>
<wire x1="-2.032" y1="-2.032" x2="0" y2="-2.032" width="0.254" layer="94" curve="-253.739795" cap="flat"/>
<wire x1="-2.54" y1="0" x2="-1.524" y2="-2.032" width="0.254" layer="94" curve="-126.869898" cap="flat"/>
<wire x1="-2.794" y1="0.762" x2="-1.778" y2="0.762" width="0.254" layer="94"/>
<wire x1="-1.016" y1="0.762" x2="0" y2="0.762" width="0.254" layer="94"/>
<wire x1="0.762" y1="0.762" x2="1.778" y2="0.762" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.762" x2="3.556" y2="0.762" width="0.254" layer="94"/>
<wire x1="4.318" y1="0.762" x2="5.334" y2="0.762" width="0.254" layer="94"/>
<text x="-2.34" y="1.27" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.048" y="-4.572" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="7.62" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="Z?CCW" prefix="L" uservalue="yes">
<description>&lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
free-suspension choke/nominal inductance&lt;p&gt;
winding counter clockwise</description>
<gates>
<gate name="G$1" symbol="L-ZL" x="0" y="0"/>
</gates>
<devices>
<device name="15/05" package="Z15/05">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="15/07" package="Z15/07">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="15/10" package="Z15/1">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="15/15" package="Z15/15">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="15/25" package="Z15/25">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="15/30" package="Z15/3">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="14/40" package="Z15/4">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="15/56" package="Z15/56">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="Z?CW" prefix="L" uservalue="yes">
<description>&lt;b&gt;CHOKE&lt;/b&gt;&lt;p&gt;
free-suspension choke/nominal inductance&lt;p&gt;
winding clockwise</description>
<gates>
<gate name="G$1" symbol="L-ZR" x="0" y="0"/>
</gates>
<devices>
<device name="4/80" package="Z4/8">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="28S/20" package="Z28S/2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="4/22" package="Z4/22">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="27/24" package="Z27/24">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="4/47" package="Z4/47">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="4/55" package="Z4/55">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="28/70" package="Z28/7">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="4/100" package="Z4/10">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="4/150" package="Z4/15">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="4/250" package="Z4/25">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="4/28" package="Z4/28">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="diode">
<description>&lt;b&gt;Diodes&lt;/b&gt;&lt;p&gt;
Based on the following sources:
&lt;ul&gt;
&lt;li&gt;Motorola : www.onsemi.com
&lt;li&gt;Fairchild : www.fairchildsemi.com
&lt;li&gt;Philips : www.semiconductors.com
&lt;li&gt;Vishay : www.vishay.de
&lt;/ul&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="SOT23">
<description>&lt;B&gt;DIODE&lt;/B&gt;</description>
<wire x1="1.4224" y1="0.6604" x2="1.4224" y2="-0.6604" width="0.1524" layer="51"/>
<wire x1="1.4224" y1="-0.6604" x2="-1.4224" y2="-0.6604" width="0.1524" layer="51"/>
<wire x1="-1.4224" y1="-0.6604" x2="-1.4224" y2="0.6604" width="0.1524" layer="51"/>
<wire x1="-1.4224" y1="0.6604" x2="1.4224" y2="0.6604" width="0.1524" layer="51"/>
<wire x1="-1.4224" y1="-0.1524" x2="-1.4224" y2="0.6604" width="0.1524" layer="21"/>
<wire x1="-1.4224" y1="0.6604" x2="-0.8636" y2="0.6604" width="0.1524" layer="21"/>
<wire x1="1.4224" y1="0.6604" x2="1.4224" y2="-0.1524" width="0.1524" layer="21"/>
<wire x1="0.8636" y1="0.6604" x2="1.4224" y2="0.6604" width="0.1524" layer="21"/>
<smd name="3" x="0" y="1.1" dx="1" dy="1.4" layer="1"/>
<smd name="2" x="0.95" y="-1.1" dx="1" dy="1.4" layer="1"/>
<smd name="1" x="-0.95" y="-1.1" dx="1" dy="1.4" layer="1"/>
<text x="-1.905" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.2286" y1="0.7112" x2="0.2286" y2="1.2954" layer="51"/>
<rectangle x1="0.7112" y1="-1.2954" x2="1.1684" y2="-0.7112" layer="51"/>
<rectangle x1="-1.1684" y1="-1.2954" x2="-0.7112" y2="-0.7112" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="KA2KA">
<wire x1="-1.27" y1="1.27" x2="-3.81" y2="0" width="0.254" layer="94"/>
<wire x1="-3.81" y1="0" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-3.81" y1="-1.27" x2="-3.81" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="-3.81" y2="0" width="0.1524" layer="94"/>
<wire x1="-1.27" y1="-1.27" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="-3.81" y1="0" x2="-3.81" y2="1.27" width="0.254" layer="94"/>
<wire x1="3.81" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="3.81" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-3.81" y1="0" x2="1.27" y2="0" width="0.1524" layer="94"/>
<wire x1="2.54" y1="0" x2="1.27" y2="0" width="0.1524" layer="94"/>
<wire x1="3.81" y1="-1.27" x2="3.81" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<circle x="0" y="0" radius="0.127" width="0.4064" layer="94"/>
<text x="0.762" y="2.0066" size="1.778" layer="95">&gt;NAME</text>
<text x="-4.826" y="-3.4544" size="1.778" layer="96">&gt;VALUE</text>
<pin name="C" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
<pin name="A" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
<pin name="AC" x="0" y="2.54" visible="off" length="short" direction="pas" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="DIODE_2CACA-" prefix="D" uservalue="yes">
<description>&lt;b&gt;2 Diodes - Cathode-Anode|Cathode-Anode&lt;/b&gt;</description>
<gates>
<gate name="-B1" symbol="KA2KA" x="0" y="0"/>
</gates>
<devices>
<device name="SOT23" package="SOT23">
<connects>
<connect gate="-B1" pin="A" pad="1"/>
<connect gate="-B1" pin="AC" pad="3"/>
<connect gate="-B1" pin="C" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="L1" library="inductor-neosid" deviceset="Z?CCW" device="14/40"/>
<part name="L2" library="inductor-neosid" deviceset="Z?CW" device="4/150"/>
<part name="D1" library="diode" deviceset="DIODE_2CACA-" device="SOT23"/>
<part name="L3" library="inductor-neosid" deviceset="Z?CCW" device="14/40"/>
<part name="L4" library="inductor-neosid" deviceset="Z?CW" device="4/150"/>
<part name="D2" library="diode" deviceset="DIODE_2CACA-" device="SOT23"/>
<part name="L5" library="inductor-neosid" deviceset="Z?CCW" device="14/40"/>
<part name="L6" library="inductor-neosid" deviceset="Z?CW" device="4/150"/>
<part name="D3" library="diode" deviceset="DIODE_2CACA-" device="SOT23"/>
<part name="L7" library="inductor-neosid" deviceset="Z?CCW" device="14/40"/>
<part name="L8" library="inductor-neosid" deviceset="Z?CW" device="4/150"/>
<part name="D4" library="diode" deviceset="DIODE_2CACA-" device="SOT23"/>
</parts>
<sheets>
<sheet>
<plain>
<wire x1="5.08" y1="83.82" x2="5.08" y2="63.5" width="0.1524" layer="97" style="shortdash"/>
<wire x1="5.08" y1="63.5" x2="35.56" y2="63.5" width="0.1524" layer="97" style="shortdash"/>
<wire x1="35.56" y1="63.5" x2="35.56" y2="83.82" width="0.1524" layer="97" style="shortdash"/>
<wire x1="35.56" y1="83.82" x2="5.08" y2="83.82" width="0.1524" layer="97" style="shortdash"/>
<wire x1="5.08" y1="60.96" x2="5.08" y2="40.64" width="0.1524" layer="97" style="shortdash"/>
<wire x1="5.08" y1="40.64" x2="35.56" y2="40.64" width="0.1524" layer="97" style="shortdash"/>
<wire x1="35.56" y1="40.64" x2="35.56" y2="60.96" width="0.1524" layer="97" style="shortdash"/>
<wire x1="35.56" y1="60.96" x2="5.08" y2="60.96" width="0.1524" layer="97" style="shortdash"/>
<wire x1="-2.54" y1="83.82" x2="-33.02" y2="83.82" width="0.1524" layer="97" style="shortdash"/>
<wire x1="-33.02" y1="83.82" x2="-33.02" y2="63.5" width="0.1524" layer="97" style="shortdash"/>
<wire x1="-33.02" y1="63.5" x2="-2.54" y2="63.5" width="0.1524" layer="97" style="shortdash"/>
<wire x1="-2.54" y1="63.5" x2="-2.54" y2="83.82" width="0.1524" layer="97" style="shortdash"/>
<wire x1="-2.54" y1="60.96" x2="-33.02" y2="60.96" width="0.1524" layer="97" style="shortdash"/>
<wire x1="-33.02" y1="60.96" x2="-33.02" y2="40.64" width="0.1524" layer="97" style="shortdash"/>
<wire x1="-33.02" y1="40.64" x2="-2.54" y2="40.64" width="0.1524" layer="97" style="shortdash"/>
<wire x1="-2.54" y1="40.64" x2="-2.54" y2="60.96" width="0.1524" layer="97" style="shortdash"/>
</plain>
<instances>
<instance part="L1" gate="G$1" x="15.24" y="48.26"/>
<instance part="L2" gate="G$1" x="17.78" y="53.34"/>
<instance part="D1" gate="-B1" x="33.02" y="50.8" rot="R90"/>
<instance part="L3" gate="G$1" x="-22.86" y="48.26"/>
<instance part="L4" gate="G$1" x="-20.32" y="53.34"/>
<instance part="D2" gate="-B1" x="-5.08" y="50.8" rot="R90"/>
<instance part="L5" gate="G$1" x="15.24" y="71.12"/>
<instance part="L6" gate="G$1" x="17.78" y="76.2"/>
<instance part="D3" gate="-B1" x="33.02" y="73.66" rot="R90"/>
<instance part="L7" gate="G$1" x="-22.86" y="71.12"/>
<instance part="L8" gate="G$1" x="-20.32" y="76.2"/>
<instance part="D4" gate="-B1" x="-5.08" y="73.66" rot="R90"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="L2" gate="G$1" pin="2"/>
<wire x1="25.4" y1="53.34" x2="27.94" y2="53.34" width="0.1524" layer="91"/>
<wire x1="27.94" y1="53.34" x2="27.94" y2="50.8" width="0.1524" layer="91"/>
<pinref part="D1" gate="-B1" pin="AC"/>
<wire x1="27.94" y1="50.8" x2="30.48" y2="50.8" width="0.1524" layer="91"/>
<wire x1="27.94" y1="50.8" x2="27.94" y2="48.26" width="0.1524" layer="91"/>
<junction x="27.94" y="50.8"/>
<pinref part="L1" gate="G$1" pin="2"/>
<wire x1="27.94" y1="48.26" x2="22.86" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="L4" gate="G$1" pin="2"/>
<wire x1="-12.7" y1="53.34" x2="-10.16" y2="53.34" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="53.34" x2="-10.16" y2="50.8" width="0.1524" layer="91"/>
<pinref part="D2" gate="-B1" pin="AC"/>
<wire x1="-10.16" y1="50.8" x2="-7.62" y2="50.8" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="50.8" x2="-10.16" y2="48.26" width="0.1524" layer="91"/>
<junction x="-10.16" y="50.8"/>
<pinref part="L3" gate="G$1" pin="2"/>
<wire x1="-10.16" y1="48.26" x2="-15.24" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="ROW_2_RESET(GND)" class="0">
<segment>
<pinref part="D2" gate="-B1" pin="C"/>
<wire x1="-5.08" y1="45.72" x2="-5.08" y2="43.18" width="0.1524" layer="91"/>
<pinref part="D1" gate="-B1" pin="C"/>
<wire x1="33.02" y1="45.72" x2="33.02" y2="43.18" width="0.1524" layer="91"/>
<wire x1="33.02" y1="43.18" x2="43.18" y2="43.18" width="0.1524" layer="91"/>
<wire x1="-5.08" y1="43.18" x2="33.02" y2="43.18" width="0.1524" layer="91"/>
<junction x="33.02" y="43.18"/>
<label x="43.18" y="43.18" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="ROW_2_SET(+24V)" class="0">
<segment>
<pinref part="D2" gate="-B1" pin="A"/>
<wire x1="-5.08" y1="55.88" x2="-5.08" y2="58.42" width="0.1524" layer="91"/>
<pinref part="D1" gate="-B1" pin="A"/>
<wire x1="33.02" y1="55.88" x2="33.02" y2="58.42" width="0.1524" layer="91"/>
<wire x1="33.02" y1="58.42" x2="43.18" y2="58.42" width="0.1524" layer="91"/>
<wire x1="-5.08" y1="58.42" x2="33.02" y2="58.42" width="0.1524" layer="91"/>
<junction x="33.02" y="58.42"/>
<label x="43.18" y="58.42" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="L6" gate="G$1" pin="2"/>
<wire x1="25.4" y1="76.2" x2="27.94" y2="76.2" width="0.1524" layer="91"/>
<wire x1="27.94" y1="76.2" x2="27.94" y2="73.66" width="0.1524" layer="91"/>
<pinref part="D3" gate="-B1" pin="AC"/>
<wire x1="27.94" y1="73.66" x2="30.48" y2="73.66" width="0.1524" layer="91"/>
<wire x1="27.94" y1="73.66" x2="27.94" y2="71.12" width="0.1524" layer="91"/>
<junction x="27.94" y="73.66"/>
<pinref part="L5" gate="G$1" pin="2"/>
<wire x1="27.94" y1="71.12" x2="22.86" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="FP2800_COLUMN_2(+24V/GND)" class="0">
<segment>
<pinref part="L6" gate="G$1" pin="1"/>
<wire x1="12.7" y1="76.2" x2="7.62" y2="76.2" width="0.1524" layer="91"/>
<wire x1="7.62" y1="76.2" x2="7.62" y2="73.66" width="0.1524" layer="91"/>
<wire x1="7.62" y1="73.66" x2="2.54" y2="73.66" width="0.1524" layer="91"/>
<pinref part="L5" gate="G$1" pin="1"/>
<wire x1="10.16" y1="71.12" x2="7.62" y2="71.12" width="0.1524" layer="91"/>
<wire x1="7.62" y1="71.12" x2="7.62" y2="73.66" width="0.1524" layer="91"/>
<junction x="7.62" y="73.66"/>
<pinref part="L2" gate="G$1" pin="1"/>
<wire x1="12.7" y1="53.34" x2="7.62" y2="53.34" width="0.1524" layer="91"/>
<wire x1="7.62" y1="53.34" x2="7.62" y2="50.8" width="0.1524" layer="91"/>
<wire x1="7.62" y1="50.8" x2="2.54" y2="50.8" width="0.1524" layer="91"/>
<pinref part="L1" gate="G$1" pin="1"/>
<wire x1="10.16" y1="48.26" x2="7.62" y2="48.26" width="0.1524" layer="91"/>
<wire x1="7.62" y1="48.26" x2="7.62" y2="50.8" width="0.1524" layer="91"/>
<junction x="7.62" y="50.8"/>
<wire x1="2.54" y1="73.66" x2="2.54" y2="50.8" width="0.1524" layer="91"/>
<wire x1="2.54" y1="50.8" x2="2.54" y2="33.02" width="0.1524" layer="91"/>
<junction x="2.54" y="50.8"/>
<label x="2.54" y="33.02" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="L8" gate="G$1" pin="2"/>
<wire x1="-12.7" y1="76.2" x2="-10.16" y2="76.2" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="76.2" x2="-10.16" y2="73.66" width="0.1524" layer="91"/>
<pinref part="D4" gate="-B1" pin="AC"/>
<wire x1="-10.16" y1="73.66" x2="-7.62" y2="73.66" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="73.66" x2="-10.16" y2="71.12" width="0.1524" layer="91"/>
<junction x="-10.16" y="73.66"/>
<pinref part="L7" gate="G$1" pin="2"/>
<wire x1="-10.16" y1="71.12" x2="-15.24" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="FP2800_COLUMN_1(+24V/GND)" class="0">
<segment>
<pinref part="L8" gate="G$1" pin="1"/>
<wire x1="-25.4" y1="76.2" x2="-30.48" y2="76.2" width="0.1524" layer="91"/>
<wire x1="-30.48" y1="76.2" x2="-30.48" y2="73.66" width="0.1524" layer="91"/>
<wire x1="-30.48" y1="73.66" x2="-35.56" y2="73.66" width="0.1524" layer="91"/>
<pinref part="L7" gate="G$1" pin="1"/>
<wire x1="-27.94" y1="71.12" x2="-30.48" y2="71.12" width="0.1524" layer="91"/>
<wire x1="-30.48" y1="71.12" x2="-30.48" y2="73.66" width="0.1524" layer="91"/>
<junction x="-30.48" y="73.66"/>
<pinref part="L4" gate="G$1" pin="1"/>
<wire x1="-25.4" y1="53.34" x2="-30.48" y2="53.34" width="0.1524" layer="91"/>
<wire x1="-30.48" y1="53.34" x2="-30.48" y2="50.8" width="0.1524" layer="91"/>
<wire x1="-30.48" y1="50.8" x2="-35.56" y2="50.8" width="0.1524" layer="91"/>
<pinref part="L3" gate="G$1" pin="1"/>
<wire x1="-27.94" y1="48.26" x2="-30.48" y2="48.26" width="0.1524" layer="91"/>
<wire x1="-30.48" y1="48.26" x2="-30.48" y2="50.8" width="0.1524" layer="91"/>
<junction x="-30.48" y="50.8"/>
<wire x1="-35.56" y1="73.66" x2="-35.56" y2="50.8" width="0.1524" layer="91"/>
<wire x1="-35.56" y1="50.8" x2="-35.56" y2="27.94" width="0.1524" layer="91"/>
<junction x="-35.56" y="50.8"/>
<label x="-35.56" y="27.94" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="ROW_1_RESET(GND)" class="0">
<segment>
<pinref part="D4" gate="-B1" pin="C"/>
<wire x1="-5.08" y1="68.58" x2="-5.08" y2="66.04" width="0.1524" layer="91"/>
<pinref part="D3" gate="-B1" pin="C"/>
<wire x1="33.02" y1="68.58" x2="33.02" y2="66.04" width="0.1524" layer="91"/>
<wire x1="33.02" y1="66.04" x2="43.18" y2="66.04" width="0.1524" layer="91"/>
<wire x1="-5.08" y1="66.04" x2="33.02" y2="66.04" width="0.1524" layer="91"/>
<junction x="33.02" y="66.04"/>
<label x="43.18" y="66.04" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="ROW_1_SET(+24V)" class="0">
<segment>
<pinref part="D4" gate="-B1" pin="A"/>
<wire x1="-5.08" y1="78.74" x2="-5.08" y2="81.28" width="0.1524" layer="91"/>
<pinref part="D3" gate="-B1" pin="A"/>
<wire x1="33.02" y1="78.74" x2="33.02" y2="81.28" width="0.1524" layer="91"/>
<wire x1="33.02" y1="81.28" x2="43.18" y2="81.28" width="0.1524" layer="91"/>
<wire x1="-5.08" y1="81.28" x2="33.02" y2="81.28" width="0.1524" layer="91"/>
<junction x="33.02" y="81.28"/>
<label x="43.18" y="81.28" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
