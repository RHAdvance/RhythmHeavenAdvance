#include "global.h"
#include "text.h"


/* Game Text - The Bon Odori */


const char D_080676b4[] = "The first half was kinda rough...";

const char D_080676d4[] = "The first half was really good!";

const char D_080676ec[] = "The second half was sorta sloppy.";

const char D_08067710[] = "The second half was incredible!";

const char D_0806772c[] = "";

const char D_08067730[] = "It really ramped up near the end!";

const char D_08067754[] = "The ending was pitch perfect!";

const char D_08067778[] = "The Audience Says";

const char text_bon_odori_ha[] = ".0:0" "‚g‚‚`";

const char text_bon_odori_hanabi_agare_ba[] = ".0:0" "‚g‚‚‚‚‚‚‰@‚`‚‡‚‚’‚…@‚‚‚`";

const char text_bon_odori_don_don_pan_pan[] = ".1:0" "‚c‚|‚@‚„‚|‚@" ".2:0" "‚‚|‚@‚‚|‚";

const char text_bon_odori_dondo_pan_pan[] = ".1:0" "‚c‚‚‚„‚@" ".2:0" "‚‚|‚@‚‚‚";

const char text_bon_odori_haa[] = ".0:0" "‚g‚`@‚`‚ˆ`";

const char text_bon_odori_kansei_agaru[] = ".0:0" "‚j‚‚‚“‚…‚‰@‚`‚‡‚‚’‚•`";

const char text_bon_odori_ninki_agare_ba[] = ".0:0" "‚m‚‰‚‚‹‚‰@‚`‚‡‚‚’‚…@‚‚‚`";

const char text_bon_odori_kyuryo_agaru[] = ".0:0" "‚j‚™‚•‚’‚™‚‚•@‚`‚‡‚‚’‚•`";

const char text_bon_odori_matsuri_da_wasshoi[] = ".0:0" "‚l‚‚”‚“‚•‚’‚‰@‚„‚@‚v‚‚“‚“‚ˆ‚‚‰I";

const char text_bon_odori_dondo_panpa_dondo_panpa[] = ".1:0" "‚c‚‚‚„‚@" ".2:0" "‚‚‚‚‚@" ".1:0" "‚„‚‚‚„‚@" ".2:0" "‚‚‚‚‚";

const char text_bon_odori_nippon_chu_ga_wasshoi[] = ".0:0" "‚m‚‰‚‚‚‚@‚ƒ‚ˆ‚•@‚‡‚@‚v‚‚“‚“‚ˆ‚‚‰I";

const char text_bon_odori_don_don_pan[] = ".1:0" "‚c‚|‚@‚„‚|‚@" ".2:0" "‚‚‚";

const char text_bon_odori_sore_hikkuri_kaette[] = ".0:0" "‚r‚‚’‚…@‚g‚‰‚‹‚‹‚•‚’‚‰@‚j‚‚…‚”‚”‚…";

const char text_bon_odori_ha_bon_odori[] = ".0:0" "‚g‚`@‚a‚‚@‚n‚„‚‚’‚‰";

const char text_bon_odori_dondo_panpa[] = ".1:0" "‚c‚‚‚„‚@" ".2:0" "‚‚‚‚‚";

const char text_bon_odori_don_pan_pan[] = ".1:0" "‚c‚|‚@" ".2:0" "‚‚|‚@‚‚‚";

const char text_bon_odori_ame_ga_agare_ba[] = ".0:0" "‚`‚‚…@‚‡‚@‚`‚‡‚‚’‚…@‚‚‚`";

const char text_bon_odori_yagura_ni_agaru[] = ".0:0" "‚x‚‚‡‚•‚’‚@‚‚‰@‚`‚‡‚‚’‚•`";

const char text_bon_odori_hora_matsuri_da_wasshoi[] = ".0:0" "‚g‚‚’‚I@‚l‚‚”‚“‚•‚’‚‰@‚„‚@‚v‚‚“‚“‚ˆ‚‚‰I";

const char text_bon_odori_korezo[] = ".0:0" "‚j‚‚’‚…‚š‚";

const char text_bon_odori_meido_in_japan[] = ".0:0" "‚l‚‚„‚…@‚‰‚@‚i‚" ".2" "‚o‚`‚m";

const char text_bon_odori_pan_pan[] = ".2:0" "‚o‚‚@‚‚‚";

const char text_bon_odori_don_don_pan_pan_2[] = ".1:0" "‚c‚|‚@‚„‚|‚@" ".2:0" "‚‚|‚@‚‚‚";

const char D_08067a84[] = ".6:1" "‚v‚…‚Œ‚ƒ‚‚‚…@‚”‚@‚”‚ˆ‚…@‚a‚‚@‚e‚…‚“‚”‚‰‚–‚‚ŒI";

const char D_08067aa4[] = ".6:1" "‚v‚ˆ‚…‚@‚—‚…@‚“‚‚™@h‚o‚‚Ch@‚™‚‚•@‚ƒ‚Œ‚‚I";

const char D_08067ad0[] = ".6:0" "‚m‚‰‚ƒ‚…@‚ƒ‚Œ‚‚‚‚‰‚‚‡I";

const char D_08067adc[] = ".6:1" "‚v‚ˆ‚…‚@‚—‚…@‚“‚‚™@h‚o‚‚‚‚Ch@‚ƒ‚Œ‚‚@‚”‚—‚‰‚ƒ‚…I";

const char D_08067b00[] = ".6:1" "‚k‚‚‚‹‚“@‚Œ‚‰‚‹‚…@‚™‚‚•f‚–‚…@‚‡‚‚”@‚‰‚”I";

