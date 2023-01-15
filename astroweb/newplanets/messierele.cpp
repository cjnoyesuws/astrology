#include <stdio.h>
#include <math.h>
#include "kep.h"


struct star messierelements[] = {
{ "M1_NGC1952", 2451545.0, 1.459532, 0.384263, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.400000e+000 },
{ "M2_NGC7089", 2451545.0, 5.643958, 0.014254, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.500000e+000 },
{ "M3_NGC5272", 2451545.0, 3.587524, 0.495383, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.400000e+000 },
{ "M4_NGC6121", 2451545.0, 4.291765, 0.463094, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 5.900000e+000 },
{ "M5_NGC5904", 2451545.0, 4.008149, 0.036361, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 5.800000e+000 },
{ "M6_C1736-321_NGC6405", 2446614.1, 4.621632, 0.561996, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 4.600000e+000 },
{ "M7_C1750-348_NGC6475", 2446614.1, 4.681846, 0.607375, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 3.300000e+000 },
{ "M8_NGC6523", 2451545.0, 4.728970, 0.425569, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 5.800000e+000 },
{ "M9_NGC6333", 2451545.0, 4.534365, 0.323177, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.900000e+000 },
{ "M10_NGC6254", 2451545.0, 4.437936, 0.071558, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.600000e+000 },
{ "M11_C1848-063_NGC6705", 2446614.1, 4.932300, 0.109665, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.100000e+000 },
{ "M12_NGC6218", 2451545.0, 4.394739, 0.034034, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.600000e+000 },
{ "M13_NGC6205", 2451545.0, 4.370741, 0.636463, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 5.900000e+000 },
{ "M14_NGC6402", 2451545.0, 4.614651, 0.056723, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.600000e+000 },
{ "M15_NGC7078", 2451545.0, 5.628687, 0.212348, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.400000e+000 },
{ "M16_C1816-138_NGC6611", 2446614.1, 4.791365, 0.240565, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.500000e+000 },
{ "M17_NGC6618", 2451545.0, 4.803146, 0.282452, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.000000e+000 },
{ "M18_NGC6613", 2451545.0, 4.799219, 0.299033, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.900000e+000 },
{ "M19_NGC6273", 2451545.0, 4.461934, 0.458440, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.200000e+000 },
{ "M20_NGC6514", 2451545.0, 4.723734, 0.402008, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.500000e+000 },
{ "M21_C1801-225_NGC6531", 2446614.1, 4.728970, 0.392699, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.200000e+000 },
{ "M22_NGC6656", 2451545.0, 4.871214, 0.417134, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 5.100000e+000 },
{ "M23_C1753-190_NGC6494", 2446614.1, 4.694936, 0.331903, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 5.900000e+000 },
{ "M24", 2451545.0, 4.786129, 0.322595, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 4.500000e+000 },
{ "M25_C1828-192_IC4725", 2446614.1, 4.847216, 0.335976, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.200000e+000 },
{ "M26_C1842-094_NGC6694", 2446614.1, 4.906557, 0.164352, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.000000e+000 },
{ "M27_NGC6853", 2451545.0, 5.234242, 0.396481, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.100000e+000 },
{ "M28_NGC6626", 2451545.0, 4.819290, 0.434005, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.900000e+000 },
{ "M29_C2022+383_NGC6913", 2446614.1, 5.338090, 0.671661, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.500000e+000 },
{ "M30_NGC7099", 2451545.0, 5.674065, 0.404625, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.500000e+000 },
{ "M31_NGC0224", 2446614.1, 0.183260, 0.718988, 0.000000, 0.000000, 0.000000, -229.00, 0.0, 4.370000e+000 },
{ "M32_NGC0221", 2446614.1, 0.183129, 0.711949, 0.000000, 0.000000, 0.000000, -217.00, 0.0, 9.090000e+000 },
{ "M33_NGC0598", 2446614.1, 0.406269, 0.533809, 0.000000, 0.000000, 0.000000, -183.00, 0.0, 6.270000e+000 },
{ "M34_NGC1039_C0238+425", 2446614.1, 0.703368, 0.745546, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 5.800000e+000 },
{ "M35_C0605+243_NGC2168", 2446614.1, 1.605703, 0.424988, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 5.600000e+000 },
{ "M36_C0532+341_NGC1960", 2446614.1, 1.462586, 0.595448, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.500000e+000 },
{ "M37_C0549+325_NGC2099", 2446614.1, 1.533708, 0.568105, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.200000e+000 },
{ "M38_C0525+358_NGC1912", 2446614.1, 1.430297, 0.625410, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.800000e+000 },
{ "M39_C2130+482_NGC7092", 2446614.1, 5.636104, 0.844448, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 5.300000e+000 },
{ "M40", 2451545.0, 3.239331, 1.013745, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.000000e+000 },
{ "M41_C0644-206_NGC2287", 2446614.1, 1.773691, 0.361574, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 5.000000e+000 },
{ "M42_NGC1976", 2451545.0, 1.463459, 0.095120, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 4.000000e+000 },
{ "M43_NGC1982", 2451545.0, 1.464331, 0.091921, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.000000e+000 },
{ "M44_C0837+201_NGC2632", 2446614.1, 2.265874, 0.349648, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 3.900000e+000 },
{ "M45_C0344+239_Pleiades", 2446614.1, 0.986984, 0.420333, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 1.500000e+000 },
{ "M46_C0739-147_NGC2437", 2446614.1, 2.012365, 0.258018, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.600000e+000 },
{ "M47_C0734-143_NGC2422", 2446614.1, 1.989675, 0.252491, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 4.300000e+000 },
{ "M48_C0811-056_NGC2548", 2446614.1, 2.151555, 0.100647, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 5.500000e+000 },
{ "M49_NGC4472", 2451545.0, 3.271620, 0.139626, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.400000e+000 },
{ "M50_C0700-082_NGC2323", 2446614.1, 1.843940, 0.145153, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.200000e+000 },
{ "M51_NGC5194-5", 2451545.0, 3.533855, 0.823795, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.100000e+000 },
{ "M52_C2322+613_NGC7654", 2446614.1, 6.124360, 1.073668, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.200000e+000 },
{ "M53_NGC5024", 2451545.0, 3.459679, 0.317068, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.700000e+000 },
{ "M54_NGC6715", 2451545.0, 4.952808, 0.532035, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.700000e+000 },
{ "M55_NGC6809", 2451545.0, 5.148721, 0.540470, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.000000e+000 },
{ "M56_NGC6779", 2451545.0, 5.046620, 0.526799, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.200000e+000 },
{ "M57_NGC6720", 2451545.0, 4.946263, 0.576540, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.000000e+000 },
{ "M58_NGC4579", 2451545.0, 3.306090, 0.206240, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.800000e+000 },
{ "M59_NGC4621", 2451545.0, 3.324852, 0.203331, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.800000e+000 },
{ "M60_NGC4649", 2451545.0, 3.332270, 0.201586, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.800000e+000 },
{ "M61_NGC4303", 2451545.0, 3.237149, 0.077958, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.700000e+000 },
{ "M62_NGC6266", 2451545.0, 4.455826, 0.525635, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.600000e+000 },
{ "M63_NGC5055", 2451545.0, 3.472333, 0.733620, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.600000e+000 },
{ "M64_NGC4826", 2451545.0, 3.388993, 0.378446, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.500000e+000 },
{ "M65_NGC3623", 2451545.0, 2.962260, 0.228347, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.300000e+000 },
{ "M66_NGC3627", 2451545.0, 2.967932, 0.226602, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.000000e+000 },
{ "M67_C0847+120_NGC2682", 2446614.1, 2.311252, 0.207112, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.400000e+000 },
{ "M68_NGC4590", 2451545.0, 3.313944, 0.466876, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.200000e+000 },
{ "M69_NGC6637", 2451545.0, 4.849397, 0.564614, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.700000e+000 },
{ "M70_NGC6681", 2451545.0, 4.900885, 0.563741, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.100000e+000 },
{ "M71_NGC6838", 2451545.0, 5.208935, 0.327831, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.300000e+000 },
{ "M72_NGC6981", 2451545.0, 5.469426, 0.218748, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.400000e+000 },
{ "M73_NGC6994", 2451545.0, 5.492987, 0.220493, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 0.000000e+000 },
{ "M74_NGC628", 2451545.0, 0.421933, 0.275471, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.200000e+000 },
{ "M75_NGC6864", 2451545.0, 5.262604, 0.382518, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.600000e+000 },
{ "M76_NGC650-1", 2451545.0, 0.446804, 0.900008, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 1.150000e+001 },
{ "M77_NGC1068", 2451545.0, 0.709913, 0.000291, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.800000e+000 },
{ "M78_NGC2068", 2451545.0, 1.512764, 0.000873, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.000000e+000 },
{ "M79_NGC1904", 2451545.0, 1.415898, 0.428478, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.000000e+000 },
{ "M80_NGC6093", 2451545.0, 4.262967, 0.401135, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.200000e+000 },
{ "M81_NGC3031", 2451545.0, 2.598795, 1.205441, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.800000e+000 },
{ "M82_NGC3034", 2451545.0, 2.599668, 1.216204, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.400000e+000 },
{ "M83_NGC5236", 2451545.0, 3.564835, 0.521272, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 7.600000e+000 },
{ "M84_NGC4374", 2451545.0, 3.251112, 0.224857, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.300000e+000 },
{ "M85_NGC4382", 2451545.0, 3.252421, 0.317359, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.200000e+000 },
{ "M86_NGC4406", 2451545.0, 3.255912, 0.226020, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.200000e+000 },
{ "M87_NGC4486", 2451545.0, 3.275983, 0.216421, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.600000e+000 },
{ "M88_NGC4501", 2451545.0, 3.281219, 0.251618, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.500000e+000 },
{ "M89_NGC4552", 2451545.0, 3.297363, 0.219039, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.800000e+000 },
{ "M90_NGC4569", 2451545.0, 3.302163, 0.229802, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.500000e+000 },
{ "M91_NGC4548", 2451545.0, 3.296054, 0.253073, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 1.020000e+001 },
{ "M92_NGC6341", 2451545.0, 4.525202, 0.752819, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.500000e+000 },
{ "M93_C0742-237_NGC2447", 2446614.1, 2.024582, 0.415970, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.500000e+000 },
{ "M94_NGC4736", 2451545.0, 3.363686, 0.717621, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.100000e+000 },
{ "M95_NGC3351", 2451545.0, 2.809980, 0.204204, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.700000e+000 },
{ "M96_NGC3368", 2451545.0, 2.822197, 0.206240, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.200000e+000 },
{ "M97_NGC3587", 2451545.0, 2.944370, 0.960222, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 1.120000e+001 },
{ "M98_NGC4192", 2451545.0, 3.201807, 0.260054, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 1.010000e+001 },
{ "M99_NGC4254", 2451545.0, 3.223623, 0.251618, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.800000e+000 },
{ "M100_NGC4321", 2451545.0, 3.241513, 0.276053, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.400000e+000 },
{ "M101_NGC5457", 2446614.1, 3.677191, 0.949779, 0.000000, 0.000000, 0.000000, 241.00, 0.0, 8.160000e+000 },
{ "M103_C0129+604_NGC0581", 2446614.1, 0.402735, 1.058251, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 6.900000e+000 },
{ "M104_NGC4594", 2446614.1, 3.312984, 0.201586, 0.000000, 0.000000, 0.000000, 1128.00, 0.0, 9.290000e+000 },
{ "M105_NGC3379", 2451545.0, 2.826561, 0.219621, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.300000e+000 },
{ "M106_NGC4258", 2451545.0, 3.224496, 0.825541, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.300000e+000 },
{ "M107_NGC6171", 2451545.0, 4.330598, 0.227765, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.100000e+000 },
{ "M108_NGC3556", 2451545.0, 2.929971, 0.971567, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 1.000000e+001 },
{ "M109_NGC3992", 2451545.0, 3.131121, 0.931715, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 9.800000e+000 },
{ "M110_NGC205", 2451545.0, 0.176278, 0.727511, 0.000000, 0.000000, 0.000000, 0.00, 0.0, 8.000000e+000 }
};

