/*
 * yggdrasil.c 
 * Григорий Павлуненко
 * gpavlun
 * gpavlun
 * Lab5: Binary Search Trees
 * ECE 2230, Fall 2025
 * 
 * God have mercy on he who try to understand this code
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "veðrfölnir.h"

/*
function: tree_construct
---constructs the tree header

Such were his thoughts. Achilles now drew near. Like crested Mars, 
the warrior-god, he came. On his right shoulder quivered fearfully The Pelian ash, 
and from his burnished mail There streamed a light as of a blazing fire, 
Or of the rising sun. When Hector saw, He trembled, nor could venture to remain, 
But left the gates and fled away in fear.
*/
tree_t *tree_construct(){
    tree_t *yggdrasil = (tree_t *)malloc(sizeof(tree_t));
    yggdrasil->well = NULL;
    yggdrasil->ncomps = yggdrasil->nkeys = 0;
    return yggdrasil;
}
/*
function: tree_destruct
---frees all nodes and frees the header

Thus onward flew Achilles, while as fast Fled Hector in dismay, 
with hurrying feet, Beside the wall. They passed the Mount of View, 
And the wind-beaten fig-tree, 
and they ran Along the public way by which the wall Was skirted, 
till they came where from the ground The two fair springs of eddying Xanthus rise⁠— 
One pouring a warm stream from which ascends And spreads a vapor like a smoke from fire; 
The other, even in summer, sending forth A current cold as hail, or snow, or ice. 
And there were broad stone basins, fairly wrought, At which, in time of peace, 
before the Greeks Had landed on the plain, the Trojan dames And their fair daughters washed their sumptuous robes. 
Past these they swept; one fled, and one pursued⁠— A brave man fled, 
a braver followed close, And swiftly both.
*/
void tree_destruct(tree_t *yggdrasil){
    if(yggdrasil==NULL){
        printf("tree does not exist!\n");
    }else{
item_remove:
        if(yggdrasil->nkeys>0){
            tree_remove(yggdrasil, yggdrasil->well->key);
            goto item_remove;
        }
        free(yggdrasil);
    }

}
/*
function: tree_insert
--inserts a new node in the tree

He spake; and Pallas from the Olympian peaks, 
Encouraged by his words in what her thought Had planned already, downward shot to earth. 
Still, with quick steps, the fleet Achilles pressed On Hector’s flight. 
As when a hound has roused A fawn from its retreat among the hills, 
And chases it through glen and forest ground. And to close thickets, 
where it skulks in fear Until he overtake it, Hector thus Sought vainly to elude the fleet pursuit Of Peleus’ son. 
As often as he thought, By springing toward the gates of Troy, 
to gain Aid from the weapons of his friends who stood On the tall towers, 
so often was the Greek Before him, forcing him to turn away From Ilium toward the plain. 
Achilles thus Kept nearest to the city. As in dreams The fleet pursuer cannot overtake, 
Nor the pursued escape, so was it now; One followed but in vain, the other fled As fruitlessly. 
But how could Hector thus Have put aside the imminent doom of death, Had not Apollo met him once again, 
For the last time, and given him strength and speed?
*/
int tree_insert(tree_t *yggdrasil, tree_key_t key, data_t *realm){
    if(yggdrasil==NULL){
        printf("tree does not exist!\n");
        return -1;
    }
    data_t *search = tree_search(yggdrasil, key);
    /*case for item already existing in the list*/
    if(search!=NULL){
        node_t *position = yggdrasil->well;
preexisting_search:
        if(position->key>key){
            position = position->left;
            goto preexisting_search;
        }else if(position->key<key){
            position = position->reft;
            goto preexisting_search;
        }else{
            position->data_ptr = realm;
        }
        return 0;
    }
    /*case for item not in list already*/
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data_ptr = realm;
    new_node->key = key;
    new_node->left = new_node->reft = NULL;
    node_t *position = yggdrasil->well;
    /*if there are no items in the list*/
    if(position==NULL){             
        yggdrasil->well = new_node;
        goto insert_return;
    }
    yggdrasil->ncomps = 0;
    /*search for new position*/
insert_search:
    yggdrasil->ncomps++;
    /*if current position is larger, go left*/
    if(position->key>key){  
        if(position->left==NULL){
            position->left = new_node;
            goto insert_return;
        }else{
            position = position->left;
            goto insert_search;
        }
    /*if current position is smaller, go right*/
    }else{                  
        if(position->reft==NULL){
            position->reft = new_node;
            goto insert_return;
        }else{
            position = position->reft;
            goto insert_search;
        }        
    }
insert_return:
    yggdrasil->nkeys++;
    return 1;
}
/*
function: remove_helper
--the recursive part of the remove function

The great Achilles nodded to his host A sign that no man should presume to-
 strike At Hector with his weapon, lest perchance Another, wounding him, 
 should bear away The glory, and Pelides only wear The second honors. 
 When the twain had come For the fourth time beside Scamander’s springs, 
 The All-Father raised the golden balance high, And, 
 placing in the scales two lots which bring Death’s long dark sleep⁠—one lot for Peleus’ son, 
 And one for knightly Hector⁠—by the midst He poised the balance. 
 Hector’s fate sank down To Hades, and Apollo left the field.
*/
data_t *remove_helper(node_t *position, node_t *previous, tree_key_t key){
    data_t *return_data;
    if(position->left!=NULL){
        node_t *ratatosk = position;
        data_t *tempdata;
        tree_key_t tempkey;
        previous = ratatosk;
        ratatosk = ratatosk->left;
        go_right:
        if(ratatosk->reft!=NULL){
            previous = ratatosk;
            ratatosk = ratatosk->reft;
            goto go_right;
        }
        /*perform data swap*/
        tempdata = position->data_ptr;
        tempkey = position->key;
        position->data_ptr = ratatosk->data_ptr;
        position->key = ratatosk->key;
        ratatosk->data_ptr = tempdata;
        ratatosk->key = tempkey;
        position = ratatosk;
        /*end data swap*/
        return remove_helper(position, previous, key);
    }else{
        if(previous->reft==position){
            previous->reft = position->reft;
        }else if(previous->left==position){
            previous->left = position->reft;
        }else if(previous==position){
            return NULL;
        }
        return_data = position->data_ptr;
        free(position);
        return return_data;
    }
}
/*
function: tree_remove
--removes the node from the tree with the given key

“Hard pressed I find thee, brother, by the swift Achilles, who, 
with feet that never rest, Pursues thee round the walls of Priam’s town. 
But let us make a stand and beat him back.”
And then the crested Hector spake in turn: 
“Deïphobus, thou ever hast been dear To me beyond my other brethren, 
sons Of Hecuba and Priam. Now still more I honor thee, since thou hast seen my plight, 
And for my sake hast ventured forth without The gates, while all the rest remain within.”
*/
data_t *tree_remove(tree_t *yggdrasil,tree_key_t key){
    if(yggdrasil==NULL){
        printf("tree does not exist!\n");
        return NULL;
    }
    data_t *search = tree_search(yggdrasil, key);
    /*case for item not in the list*/
    if(search==NULL){
        return NULL;
    }
    node_t *position = yggdrasil->well;
    node_t *previous = yggdrasil->well;
    data_t *return_data = NULL;
remove_search:
    if(position->key!=key){
        previous = position;
        if(position->key>key){
            position = position->left;
        }else{
            position = position->reft;
        }
        goto remove_search;
    }
    return_data = remove_helper(position, previous, key);
    if(return_data==NULL){
        yggdrasil->well = position->reft;
        return_data = position->data_ptr;
        free(position);         
    }
    yggdrasil->nkeys--;
    return return_data;
}
/*
function: tree_search
--finds a node in the list with a matching key

Piangevisi entro l’arte per che, morta,
Deïdamìa ancor si duol d’Achille,
e del Palladio pena vi si porta.  
(Inf. 26.61-63)

There they regret the guile that makes the dead
Deidamia still lament Achilles;
and there, for the Palladium,they pay.
*/
data_t *tree_search(tree_t *yggdrasil, tree_key_t key){
    if(yggdrasil==NULL){
        printf("tree does not exist!\n");
        return NULL;
    }
    node_t *position = yggdrasil->well;
    yggdrasil->ncomps = 0;
position_search:
    if(position==NULL){
        return NULL;
    }
    if(position->key==key){
        yggdrasil->ncomps++;
        return position->data_ptr;
    }else if(position->key>key){
        yggdrasil->ncomps++;
        yggdrasil->ncomps++;
        position = position->left;
        goto position_search;
    }else{
        yggdrasil->ncomps++;
        yggdrasil->ncomps++;
        position = position->reft;
        goto position_search;
    }
}
/*
function: tree_level
--finds the level of the node with the given key

“No longer I avoid thee as of late, O son of Peleus! 
Thrice around the walls Of Priam’s mighty city have I fled, 
Nor dared to wait thy coming. Now my heart Bids me encounter thee; 
my time is come To slay or to be slain. Now let us call The gods to witness, 
who attest and guard The covenants of men. Should Jove bestow On me the victory, 
and I take thy life, Thou shalt meet no dishonor at my hands; But, 
stripping off the armor, I will send The Greeks thy body. Do the like by me.”
*/
int tree_level(tree_t *yggdrasil, tree_key_t key){
    if(yggdrasil==NULL){
        printf("tree does not exist!\n");
        return -1;
    }
    node_t *ratatosk = yggdrasil->well;
    int level = 0;
level_search:
    if(ratatosk==NULL||ratatosk->key==key){
        return level;
    }else if(ratatosk->key>key){
        ratatosk = ratatosk->left;
    }else{
        ratatosk = ratatosk->reft;
    }
    level++;
    goto level_search;
}
int validate(tree_t *){
    return 1;
}
/*
function: tree_size
--returns the number of keys

He spake, and, brandishing his massive spear, Hurled it at Hector, 
who beheld its aim From where he stood. 
He stooped, and over him The brazen weapon passed, and plunged to earth. 
Unseen by royal Hector, Pallas went And plucked it from the ground, 
and brought it back And gave it to the hands of Peleus’ son, 
While Hector said to his illustrious foe:⁠—
*/
int tree_size(tree_t *yggdrasil){
    if(yggdrasil==NULL){
        printf("tree does not exist!\n");
        return -1;
    }
    return yggdrasil->nkeys;
}
/*
function: tree_stats
--returns the number of comparisons of last operation

“Godlike Achilles, thou hast missed thy mark; 
Nor hast thou learned my doom from Jupiter, As thou pretendest. 
Thou art glib of tongue. And cunningly thou orderest thy speech, 
In hope that I who hear thee may forget My might and valor. 
Think not I shall flee, That thou mayst pierce my back; 
for thou shalt send Thy spear, if God permit thee, 
through my breast As I rush on thee. Now avoid in turn My brazen weapon. 
Would that it might pass Clean through thee, all its length! 
The tasks of war For us of Troy were lighter for thy death, 
Thou pest and deadly foe of all our race!”
*/
int tree_stats(tree_t *yggdrasil){
    if(yggdrasil==NULL){
        printf("tree does not exist!\n");
        return -1;
    }
    return yggdrasil->ncomps;
}
/*
function: path_helper
--recursive part of the internal path length function

He spake, and brandishing his massive spear, Hurled it, nor missed, 
but in the centre smote The buckler of Pelides. 
Far away It bounded from the brass, 
and he was vexed To see that the swift weapon from his hand Had flown in vain. 
He stood perplexed and sad; No second spear had he. 
He called aloud On the white-bucklered chief, Deïphobus, To bring another; but that chief was far, 
And Hector saw that it was so, and said:⁠—
*/
int path_helper(node_t *ratatosk, int level, int levelsum){
    int leftlevel = level;
    int reftlevel = level;
    if(ratatosk->left!=NULL){
        leftlevel++;
        levelsum = path_helper(ratatosk->left, leftlevel, levelsum);
    } 
    if(ratatosk->reft!=NULL){
        reftlevel++;
        levelsum = path_helper(ratatosk->reft, reftlevel, levelsum);
    }
    return levelsum + level;
}
/*
function: tree_internal_path_len
--finds the internal path length of the tree

“Ah me! The gods have summoned me to die. I thought my warrior-friend, Deïphobus, 
Was by my side; but he is still in Troy, And Pallas has deceived me. 
Now my death Cannot be far⁠—is near; there is no hope Of my escape, 
for so it pleases Jove And Jove’s great archer-son, who have till now Delivered me. 
My hour at last is come; Yet not ingloriously or passively I die, 
but first will do some valiant deed, Of which mankind shall hear in after time.”
*/
int tree_internal_path_len(tree_t *yggdrasil){
    if(yggdrasil==NULL){
        printf("tree does not exist!\n");
        return -1;
    }
    int level = 0;
    int levelsum = 0;
    node_t *ratatosk = yggdrasil->well;
    if(ratatosk==NULL) return level;
    return path_helper(ratatosk, level, levelsum);
}

void print_helper(node_t *ratatosk){
    if(ratatosk!=NULL){
        if(ratatosk->left!=NULL){
            print_helper(ratatosk->left);
        } 
        if(ratatosk->reft!=NULL){
            print_helper(ratatosk->reft);
        }
        printf("[key %d -- data %d]\n",ratatosk->key,*(ratatosk->data_ptr));
    }
}
void tree_debug_print_tree(tree_t *yggdrasil){
    if(yggdrasil==NULL){
        printf("tree does not exist!\n");
    }else{
        printf("======TREE======\n");
        printf("keys-%d ncomps-%d\n",yggdrasil->nkeys,yggdrasil->ncomps);
        print_helper(yggdrasil->well);
        printf("==done printing==\n");
    }

}
void tree_debug_validate(tree_t *yggdrasil){
    if(yggdrasil==NULL){
        printf("tree does not exist!\n");
    }else{
        assert(validate(yggdrasil)==1);
    }
}
