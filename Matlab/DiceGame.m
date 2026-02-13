%% part 1
clc
clear
CNum=0;
pos=1;
tot=[1];
while CNum~=1
x=questdlg('Roll dice?','Dice Game','Yes','No','Yes');
if strcmpi(x,'No')||strcmpi(x,'')
    error('gameover')
else
CNum=randi([1,6]);
fprintf('rolled %0.0f\n',CNum)
tot(1,pos)=CNum;
pos=pos+1;
end
end
y=sum(tot);
fprintf('points %0.0f\n',y)
%% part 2
clc
clear
CNum=0;
pos=1;
tot=[1];
times=0;
while sum(tot)<=100
times=times+1;
CNum=0;
while CNum~=1
x=questdlg('Roll dice?','Dice Game','Yes','No','Yes');
if strcmpi(x,'No')||strcmpi(x,'')
     % In the first age, in the first battle, when the shadows first lengthened, 
     % one stood, burned by the embers of Armageddon, his soul blistered by the fires of hell 
     % and tainted beyond ascension. He chose the path of perpetual torment. 
     % In his ravenous hatred he found no peace, and with boiling blood he scoured the umbral plains 
     % seeking vengeance against the dark lords who had wronged him. 
     % He wore the crown of the knight sentinels, and those who tasted the bite of his sword name him the Doomslayer.

     %Tempered by the fires of hell, his iron will remained steadfast through the passage that preys upon the week, 
     % for he alone was the hell walker, the unchained predator who sought retribution in all quarters, 
     % dark and light, fire and ice, in he beginning and the end. 
     % And he hunted the slaves of doom with barbarous cruelty; 
     % for he passed through the divide as none but demon had before.

     %And in his conquest against the blackened souls of the doom,
     % his prowess was shown. In his crusade the seraphim bestowed upon him terrible power 
     % and speed and with his might he crushed the obsidian pillars of the blood temples. 
     % He set fourth without pity upon the beasts of the knight circles. Unbreakable, incorruptible, 
     % unyielding, the Doomslayer sought to end the dominion of the dark realm.

     %The age of his reckoning was uncounted, the scribes carved his name deep into he taverns of hell across eons, 
     % with each battle etched terror in the hearts of demons. They knew he would come, 
     % as he always had, as he always will, to feast on the blood of the wicked, 
     % for he alone could draw strength from his fallen foes, and ever his power grew swift and unrelenting.

     %None could stand before the hoard but the Doomslayer. 
     % Despair spread before him like a plague, striking fear into the shadow dwellers, 
     % driving them to deeper and darker pits. But from the depth of the abyss rose the great one, a champion, 
     % mightier then all that had come before; the Titan of immeasurable power and ferocity. 
     % He strode upon the plain and faced the Doomslayer, and a mighty battle was fought on the desolate plains. 
     % The Titan fought with the fury of the countless that had fallen at the Doomslayer%s hands; 
     % but there fell the Titan, and in his defeat the shadow hoard was routed.

     %And in his terrible rancor between worlds and through time came the wretch who shall not be named, 
     % but in his heresy was loyal to his evil cause. The wretch adored the Doomslayer in a mighty armor, 
     % wrought in the fortress of hell, impenetrable and unyielding, with sword and shield of adamantine strength, 
     % the Doomslayer sent to banish all that were left unbroken by his savagery to the void.

     %Yet as the mighty Titan fell and dread engulfed the armies of doom, 
     % the demon priests of the blood temples laid a trap to capture the scourge of hell, 
     % insatiable, even by the vanquishing of the great one, the hell walker sought to prey in the tombs of the blood keep, 
     % and blinded by his fervor, the lure drew him in. The priests brought down the temple 
     % of the Doomslayer and in his defeat entombed him in the cursed sarcophagus. The mark of the Doomslayer was burned upon his crypt, 
     % a warning to all of hell that the terror within must never be freed. There he lies still, and ever more, in silent suffering.
    error('gameover')
else
CNum=randi([1,6]);
fprintf('rolled %0.0f\n',CNum)
tot(1,pos)=CNum;
pos=pos+1;
end
end
y=sum(tot);
fprintf('points %0.0f\n',y)
end
fprintf('times played %0.0f\n',times)