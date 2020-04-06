Chebeque (AKA Xebec, Chebeke...)
Mediterranean / Arabian Flavour Frigate
1.1
23.09.2007
================================================================================
/me
[Refar]
[lord_refar@yahoo.de]

/Civ4 BTS
[Civilization 4, by Firaxis]
[Beyond the Sword Expansion]

/me is not a native english speaker, so take my apologies for any linguistical
derailments you might find in here.

Chebeque For Civ4 BTS
================================================================================
From all i know, the unit will work with Vanilla and Warlords as well. However
only BTS was actually tested. 

This kind of ship was widely used in the Mediterranean. While in general smaller
and weaker than the north european Frigate, the ship often filled the same
role. Hence it seems to be a appropriate Frigate Flavour replacement for Arabic,
Mediterranean and perhaps African Civ's

Installation
================================================================================
I suggest copying/using the ART_DEF_UNIT_FRIGATE as base.
<NIF> --> Xebec.nif
<SHADERNIF> --> Xebec_FX.nif

If you not like one of them, you can use one (Normal or FX) version for both
NIF and SHADERNIF

<KFM> --> Xebec.kfm
<Button> --> Xebec_Icon.dds, if you wish to use the included Button.
Keep the Frigates Sound defines or add them.
		<TrainSound>AS2D_UNIT_BUILD_UNIT</TrainSound>
		<AudioRunSounds>
			<AudioRunTypeLoop>LOOPSTEP_OCEAN2</AudioRunTypeLoop>
			<AudioRunTypeEnd>ENDSTEP_OCEAN2</AudioRunTypeEnd>
		</AudioRunSounds>
		<SelectionSound>AS3D_UN_OCEAN_END1</SelectionSound>
		<ActionSound>AS3D_UN_OCEAN_END1</ActionSound>

Suggestions for other relevant tags:
I scaled the model very similar to the Frigate, so you should be able to use the
same values. 
	<fScale>0.23</fScale> (0.17 will more or less fit the ship in one plot)
	<fInterfaceScale>1.0</fInterfaceScale>

	<ShadowDef>
		<ShadowNIF>Art/Units/01_UnitShadows/FrigateShadow.nif</ShadowNIF>
		<ShadowAttachNode>BIP Pelvis</ShadowAttachNode>
		<fShadowScale>1.0</fShadowScale>

If the hints above do not have any meaning to you, here you can find tutorials
and information about adding units:
http://forums.civfanatics.com/forumdisplay.php?f=177

!!! NOTE !!!: BronenosetsRope.dds is in the Archive, while it comes from 
another unit of mine. 
It is not a mistake, the File is used for the rigging.

Credits
================================================================================
Model, Textures and Animation by \me.
Firaxis Sound and Effects in Game.
Useful tutorials/infos on unit editing and export came from:
Sharik http://forums.civfanatics.com/showthread.php?t=184327
Rabbit, White http://forums.civfanatics.com/showthread.php?t=163585
Thunderfall http://forums.civfanatics.com/showthread.php?t=162118

Version Changes
================================================================================
1.1 Fixing a bug causing the ShaderFX version to turn all white. (Wrong Shader
version was used)

Disclaimer
================================================================================
The mod comes 'as is' and while effort, and testing has been made to keep it 
bug-free it may content errors. If you choose to use it, i am not to be hold 
responsible for any damage that might be caused. Neither material nor spiritual. 
This mod is a non-profit fan-project and no copyright infringement is intended.