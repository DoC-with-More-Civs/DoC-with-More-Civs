HORSE ARCHER ARROWS MANAGEMENT

If you wish to preserve the right kind of arrow during combat animation sequence, you must:

1) append the following code into your modded CIV4EffectInfos.xml, editing the <Path> rows below:

		<!--horsearcher arrows:-->
		<EffectInfo>
			<Type>EFFECT_EGYPTIANARROW1</Type>
			<Description>ChineseArcherArrow</Description>
			<fScale>1.0</fScale>
			<fUpdateRate>1.0</fUpdateRate>
			<Path>[...your path...]/anim_effects/aco_arrow1.nif</Path>
			<bIsProjectile>1</bIsProjectile>
			<fSpeed>500.0</fSpeed>
			<fArcValue>0.0</fArcValue>
		</EffectInfo>
		<EffectInfo>
			<Type>EFFECT_EGYPTIANARROW2</Type>
			<Description>ChineseArcherArrow</Description>
			<fScale>1.0</fScale>
			<fUpdateRate>1.0</fUpdateRate>
			<Path>[...your path...]/anim_effects/aco_arrow2.nif</Path>
			<bIsProjectile>1</bIsProjectile>
			<fSpeed>500.0</fSpeed>
			<fArcValue>0.0</fArcValue>
		</EffectInfo>

2) address the right kind of kfm into <KFM> rows of your modded CIV4ArtDefines_Unit.xml as follow:

for horsearchers using light brown arrows:
			<KFM>[...your path...]/anim_comp/horsearcher_1.kfm</KFM>
 
for horsearchers using dark brown arrows:
			<KFM>[...your path...]/anim_comp/horsearcher_2.kfm</KFM>
 
During combat sequence, each modded #_kfm calls its rangedstrik#.kf animation, each #.kf calls its EFFECT_XXX xml <Type>, each EFFECT_XXX calls its effect-nif properly.
 