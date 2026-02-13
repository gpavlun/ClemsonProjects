%%Gregory Pavlunenko ENGR1410
%Problem Statement:The point of this lab is to create a script and function that will plot
%experimental data
%% VariableList
%o=attempts
%Oooo=looping variable
%oOo=Data
%oOoO=Information
%OoO=listselection
%oO=dialogbox selection
%O=colors of the trendline

clc;clear;close all;        clc;close all;clc;close all;close;  clc;
    oOoO=readtable("Cooling Data.xlsx","sheet","Information");%data reading
oOo=readmatrix("Cooling Data.xlsx","sheet","Data");
        Oooo=0;%looping variable for program termination
o=1;
            while Oooo==0
if o==1
        oO='';
o=2;
    while isempty(oO)
oO=questdlg('What type of plot do you want to create?','Plot','Summary','Detail','Detail');%dialog  for attempt#1
                                if isempty(oO)
warning('valid selection not made!')%error for no selection
            end
end
        else
oO='';
    while isempty(oO)
oO=questdlg('What type of plot do you want to create?','Plot','Summary','Detail','Stop','Stop');%dialog for attempt#1+n
    if strcmpi(oO,'Stop')
                            Oooo=2;%breaks the loop
                    end
end
            end
    if strcmpi(oO,"summary")%summary plots
        L3_Fn_gpavlun(oOo,table2array(oOoO))%summons function summary
title('Summary Plot')
                                                legend(oOoO{:,1});%creates summary legend
elseif strcmpi(oO,"detail") %detail plots
                                    OoO=listdlg('PromptString','Pick a Material','ListString',table2array(oOoO(:,1)),'SelectionMode','single');
if isempty(OoO)
        error('zoinks scoob!(selection not made)')%error if selecting nothing
end
            % In the first age, in the first battle, when the shadows first
            % lengthened, one stood, burned by the embers of Armageddon, 
            % his soul blistered by the fires of hell and tainted beyond 
            % ascension. He chose the path of perpetual torment. In his 
            % ravenous hatred he found no peace, and with boiling blood he 
            % scoured the umbral plans seeking vengeance against the dark 
            % lords who had wronged him. He wore the crown of the knight 
            % sentinels, and those who tasted the bite of his sword name 
            % him the Doomslayer.

            %Tempered by the fires of hell, his iron will remained 
            % steadfast through the passage that preys upon the week, for 
            % he alone was the hell walker, the unchained predator who 
            % sought retribution in all quarters, dark and light, fire and 
            % ice, in he beginning and the end. And he hunted the slaves of
            % doom with barbarous cruelty; for he passed through the divide 
            % as none but demon had before.

            %And in his conquest against the blackened souls of the doom, 
            % his prowess was shown. In his crusade the seraphim bestowed 
            % upon him terrible power and speed and with his might he 
            % crushed the obsidian pillars of the blood temples. He set 
            % fourth without pity upon the beasts of the knight circles. 
            % Unbreakable, incorruptible, unyielding, the Doomslayer sought 
            % to end the dominion of the dark realm.

            %The age of his reckoning was uncounted, the scribes carved his 
            % name deep into he taverns of hell across eons, with each 
            % battle etched terror in the hearts of demons. They knew he 
            % would come, as he always had, as he always will, to feast on 
            % the blood of the wicked, for he alone could draw strength 
            % from his fallen foes, and ever his power grew swift and 
            % unrelenting.

            %None could stand before the hoard but the Doomslayer. Despair 
            % spread before him like a plague, striking fear into the 
            % shadow dwellers, driving them to deeper and darker pits. 
            % But from the depth of the abyss rose the great one, a 
            % champion, mightier then all that had come before; the Titan 
            % of immeasurable power and ferocity. He strode upon the plain 
            % and faced the Doomslayer, and a mighty battle was fought on 
            % the desolate plains. The Titan fought with the fury of the 
            % countless that had fallen at the Doomslayer%s hands; but 
            % there fell the Titan, and in his defeat the shadow hoard was 
            % routed.

            %And in his terrible rancor between worlds and through time 
            % came the wretch who shall not be named, but in his heresy was 
            % loyal to his evil cause. The wretch adored the Doomslayer in 
            % a mighty armor, wrought in the fortress of hell, impenetrable 
            % and unyielding, with sword and shield of adamantine strength, 
            % the Doomslayer sent to banish all that were left unbroken by 
            % his savagery to the void.

            %Yet as the mighty Titan fell and dread engulfed the armies of 
            % doom, the demon priests of the blood temples laid a trap to 
            % capture the scourge of hell, insatiable, even by the 
            % vanquishing of the great one, the hell walker sought to prey 
            % in the tombs of the blood keep, and blinded by his fervor, 
            % the lure drew him in. The priests brought down the temple of 
            % the Doomslayer and in his defeat entombed him in the cursed 
            % sarcophagus. The mark of the Doomslayer was burned upon his 
            % crypt, a warning to all of hell that the terror within must 
            % never be freed. There he lies still, and ever more, in silent 
            % suffering.
            L3_Fn_gpavlun(oOo(OoO*2-1:OoO*2,:),table2array(oOoO(OoO,:)))%summons function for detail
title(oOoO{OoO,1})
                oOoOoOo=oOoO{OoO,2};%pOlYfIt
O=oOoOoOo{1};%color for the trendline
    C=polyfit(oOo(OoO*2-1,2:end),log(oOo(OoO*2,2:end)),1);
oOoOo=C(1);
        b=exp(C(2));
                                                    tpf=0:10;%polyfit variable combination
            Vpf=b*exp(oOoOo*tpf);
hold on; 
        plot(tpf,Vpf,'color',O(1));
X=sprintf('%0.2fe^{%0.2ft}',b,oOoOo);%plot trendline
z=oOo(OoO*2,5);
    text(1.5,z+10,X,'color',O(1),'fontsize',9,'edgecolor',O(1),'linestyle',':','linewidth',1.5,'BackgroundColor','w');%trendline equation
hold off;
                end
end
