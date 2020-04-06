Akula Submarine
1.1
30.08.2007
================================================================================
/me
[Refar]
[lord_refar@yahoo.de]
[http://www.i-mod-productions.com is the home of my mods]

/Civ4 BTS
[Civilization 4, by Firaxis]
[Beyond the Sword Expansion]

/me is not a native english speaker, so take my apologies for any linguistical
derailments you might find in here.

Akula Submarine For Civ4 BTS
================================================================================
From all i know, the unit will work with Vanilla and Warlords as well. However
only BTS was actually tested. 

The Archive contains a light (default) and a dark versions of the Texture. 
Choose which one you like and rename to AkulaDiffuse_256.dds

Installation
================================================================================
I suggest copying/using the ART_DEF_UNIT_SUBMARINE as base.
<NIF> --> Akula_Sub.nif
<SHADERNIF> --> Akula_Sub_FX.nif

If you are getting ptoblems with the FX version, or just do not like it, 
you can still use Akula_Sub.nif for the shadernif as well.

<KFM> --> Akula_Sub.kfm
<Button> --> Akula_Button.dds, if you wish to use the included Button.
Keep the submarines Sound defines or add them. 
	<TrainSound>AS2D_UNIT_BUILD_UNIT</TrainSound>
	<AudioRunSounds>
		<AudioRunTypeLoop>LOOPSTEP_SUBMARINE</AudioRunTypeLoop>
		<AudioRunTypeEnd>ENDSTEP_SUBMARINE</AudioRunTypeEnd>
	</AudioRunSounds>
	<SelectionSound>AS3D_UN_SUBMARINE_FORT</SelectionSound>
Suggestions for other relevant tags:
	<fScale>0.45</fScale> (0.45 will more or less fit the ship in one plot.
	If you like larger modern ships, values of 0.5 + might be better)
	<fInterfaceScale>1.2</fInterfaceScale>
	<fRangedDeathTime>0.6</fRangedDeathTime> (The Death animation is a bit
	longer as usual so give it a little time to play ;-)
	<ActionSound>AS3D_UN_SUBMARINE_FORT</ActionSound>

If the hints above do not have any meaning to you, here you can find tutorials
and information about adding units:
http://forums.civfanatics.com/forumdisplay.php?f=177

Credits
================================================================================
Model, Main Texture and Animation by \me.
Damage Texture is the edited nuclear sub damage map from BTS. The Unit uses 
Firaxis Sound and Effects in Game.
Useful tutorials/infos on unit editing and export came from:
Sharik http://forums.civfanatics.com/showthread.php?t=184327
Rabbit, White http://forums.civfanatics.com/showthread.php?t=163585
Thunderfall http://forums.civfanatics.com/showthread.php?t=162118

Version Changes
================================================================================
1.1 Added the FX Version of the nif file.

Disclaimer
================================================================================
The mod comes 'as is' and while effort, and testing has been made to keep it 
bug-free it may content errors. If you choose to use it, i am not to be hold 
responsible for any damage that might be caused. Neither material nor spiritual. 
This mod is a non-profit fan-project and no copyright infringement is intended.