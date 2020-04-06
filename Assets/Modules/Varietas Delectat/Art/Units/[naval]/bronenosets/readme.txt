Bronenosts (Pre Dreadnought) 
1.0
5.09.2007
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

Bronenosets For Civ4 BTS
================================================================================
From all i know, the unit will work with Vanilla and Warlords as well. However
only BTS was actually tested. 

Modeled (roughly) after the Russian Pre-Dreadnought Warship Tsesarewitch
http://ship.bsu.by/main.asp?id=102466 (Its Russian, but you can look the pics)
to serve as Ironclad in the game.

Installation
================================================================================
I suggest copying/using the ART_DEF_UNIT_IRONCLAD as base.
<NIF> --> Bronenosets.nif
<SHADERNIF> --> Bronenosets_FX.nif

If you not like one of them, you can use one (Normal or FX) version for both
NIF and SHADERNIF

<KFM> --> Bronenosets.kfm
<Button> --> Bronenosets_Button.dds, if you wish to use the included Button.
Keep the Ironclads Sound defines or add them. 
	<TrainSound>AS2D_UNIT_BUILD_UNIT</TrainSound>
	<AudioRunSounds>
		<AudioRunTypeLoop>LOOPSTEP_IRONCLAD</AudioRunTypeLoop>
		<AudioRunTypeEnd>ENDSTEP_IRONCLAD</AudioRunTypeEnd>
	</AudioRunSounds>
	<SelectionSound>AS3D_UN_IRONCLAD_FORT</SelectionSound>
	<ActionSound>AS3D_UN_IRONCLAD_FORT</ActionSound>

Suggestions for other relevant tags:
	<fScale>0.75</fScale> (will more or less fit the ship in one plot.
	If you like larger modern ships, values of 0.8 + might be better)
	<fInterfaceScale>1.0</fInterfaceScale>
	<fRangedDeathTime>0.31</fRangedDeathTime>

	<ShadowDef>
		<ShadowNIF>Art/Units/01_UnitShadows/FrigateShadow.nif</ShadowNIF>
		<ShadowAttachNode>BIP Pelvis</ShadowAttachNode>
		<fShadowScale>0.25</fShadowScale> 
		(Remember to adjust, if changing fScale)

If the hints above do not have any meaning to you, here you can find tutorials
and information about adding units:
http://forums.civfanatics.com/forumdisplay.php?f=177

Credits
================================================================================
Model, Textures and Animation by \me.
For Damage Texture the Ironclad Damage TEx from Civ4 was used as base. 
Firaxis Sound and Effects in Game.
Useful tutorials/infos on unit editing and export came from:
Sharik http://forums.civfanatics.com/showthread.php?t=184327
Rabbit, White http://forums.civfanatics.com/showthread.php?t=163585
Thunderfall http://forums.civfanatics.com/showthread.php?t=162118

Disclaimer
================================================================================
The mod comes 'as is' and while effort, and testing has been made to keep it 
bug-free it may content errors. If you choose to use it, i am not to be hold 
responsible for any damage that might be caused. Neither material nor spiritual. 
This mod is a non-profit fan-project and no copyright infringement is intended.