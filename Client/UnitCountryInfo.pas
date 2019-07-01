unit UnitCountryInfo;

interface
uses
  System.SysUtils;

function GetCountryName(ISO3166CTRYNAME: String = ''; Code: integer = -1): String;
function GetCountryImageIndex(ISO3166CTRYNAME: String): Integer;

implementation
function GetCountryName(ISO3166CTRYNAME: String = ''; Code: integer = -1): String;
begin
  ISO3166CTRYNAME := Uppercase(ISO3166CTRYNAME);
  Result := 'Unknown';

  if (ISO3166CTRYNAME = 'AF') or (Code = 0) then Result := 'Afghanistan' else
  if (ISO3166CTRYNAME = 'AX') or (Code = 1) then Result := 'Aland Islands' else
  if (ISO3166CTRYNAME = 'AL') or (Code = 2) then Result := 'Albania' else
  if (ISO3166CTRYNAME = 'DZ') or (Code = 3) then Result := 'Algeria ' else
  if (ISO3166CTRYNAME = 'AS') or (Code = 4) then Result := 'American Samoa' else
  if (ISO3166CTRYNAME = 'AD') or (Code = 5) then Result := 'Andorra' else
  if (ISO3166CTRYNAME = 'AO') or (Code = 6) then Result := 'Angola' else
  if (ISO3166CTRYNAME = 'AI') or (Code = 7) then Result := 'Anguilla' else
  if (ISO3166CTRYNAME = 'AQ') or (Code = 8) then Result := 'Antarctica' else
  if (ISO3166CTRYNAME = 'AG') or (Code = 9) then Result := 'Antigua And Barbuda' else
  if (ISO3166CTRYNAME = 'AR') or (Code = 10) then Result := 'Argentina' else
  if (ISO3166CTRYNAME = 'AM') or (Code = 11) then Result := 'Armenia' else
  if (ISO3166CTRYNAME = 'AW') or (Code = 12) then Result := 'Aruba' else
  if (ISO3166CTRYNAME = 'AU') or (Code = 13) then Result := 'Australia' else
  if (ISO3166CTRYNAME = 'AT') or (Code = 14) then Result := 'Austria' else
  if (ISO3166CTRYNAME = 'AZ') or (Code = 15) then Result := 'Azerbaijan' else
  if (ISO3166CTRYNAME = 'BS') or (Code = 16) then Result := 'Bahamas' else
  if (ISO3166CTRYNAME = 'BH') or (Code = 17) then Result := 'Bahrain' else
  if (ISO3166CTRYNAME = 'BD') or (Code = 18) then Result := 'Bangladesh' else
  if (ISO3166CTRYNAME = 'BB') or (Code = 19) then Result := 'Barbados' else
  if (ISO3166CTRYNAME = 'BY') or (Code = 20) then Result := 'Belarus' else
  if (ISO3166CTRYNAME = 'BE') or (Code = 21) then Result := 'Belgium' else
  if (ISO3166CTRYNAME = 'BZ') or (Code = 22) then Result := 'Belize' else
  if (ISO3166CTRYNAME = 'BJ') or (Code = 23) then Result := 'Benin' else
  if (ISO3166CTRYNAME = 'BM') or (Code = 24) then Result := 'Bermuda' else
  if (ISO3166CTRYNAME = 'BT') or (Code = 25) then Result := 'Bhutan' else
  if (ISO3166CTRYNAME = 'IO') or (Code = 26) then Result := 'British Indian Ocean Territory' else
  if (ISO3166CTRYNAME = 'BO') or (Code = 27) then Result := 'Bolivia, Plurinational State Of' else
  if (ISO3166CTRYNAME = 'BQ') or (Code = 28) then Result := 'Bonaire, Saint Eustatius And Saba' else
  if (ISO3166CTRYNAME = 'BA') or (Code = 29) then Result := 'Bosnia And Herzegovina' else
  if (ISO3166CTRYNAME = 'BW') or (Code = 30) then Result := 'Botswana' else
  if (ISO3166CTRYNAME = 'BV') or (Code = 31) then Result := 'Bouvet Island' else
  if (ISO3166CTRYNAME = 'BR') or (Code = 32) then Result := 'Brazil' else
  if (ISO3166CTRYNAME = 'BN') or (Code = 33) then Result := 'Brunei Darussalam' else
  if (ISO3166CTRYNAME = 'BG') or (Code = 34) then Result := 'Bulgaria' else
  if (ISO3166CTRYNAME = 'BF') or (Code = 35) then Result := 'Burkina Faso' else
  if (ISO3166CTRYNAME = 'BI') or (Code = 36) then Result := 'Burundi' else
  if (ISO3166CTRYNAME = 'KH') or (Code = 37) then Result := 'Cambodia' else
  if (ISO3166CTRYNAME = 'CM') or (Code = 38) then Result := 'Cameroon' else
  if (ISO3166CTRYNAME = 'CA') or (Code = 39) then Result := 'Canada' else
  if (ISO3166CTRYNAME = 'CV') or (Code = 40) then Result := 'Cape Verde' else
  if (ISO3166CTRYNAME = 'KY') or (Code = 41) then Result := 'Cayman Islands' else
  if (ISO3166CTRYNAME = 'CF') or (Code = 42) then Result := 'Central African Republic' else
  if (ISO3166CTRYNAME = 'TD') or (Code = 43) then Result := 'Chad' else
  if (ISO3166CTRYNAME = 'CL') or (Code = 44) then Result := 'Chile' else
  if (ISO3166CTRYNAME = 'CN') or (Code = 45) then Result := 'China' else
  if (ISO3166CTRYNAME = 'CX') or (Code = 46) then Result := 'Christmas Island' else
  if (ISO3166CTRYNAME = 'CC') or (Code = 47) then Result := 'Cocos (Keeling) Islands' else
  if (ISO3166CTRYNAME = 'CO') or (Code = 48) then Result := 'Colombia' else
  if (ISO3166CTRYNAME = 'KM') or (Code = 49) then Result := 'Comoros' else
  if (ISO3166CTRYNAME = 'CG') or (Code = 50) then Result := 'Congo' else
  if (ISO3166CTRYNAME = 'CD') or (Code = 51) then Result := 'Congo, The Democratic Republic Of The' else
  if (ISO3166CTRYNAME = 'CK') or (Code = 52) then Result := 'Cook Islands' else
  if (ISO3166CTRYNAME = 'CR') or (Code = 53) then Result := 'Costa Rica' else
  if (ISO3166CTRYNAME = 'HR') or (Code = 54) then Result := 'Croatia' else
  if (ISO3166CTRYNAME = 'CU') or (Code = 55) then Result := 'Cuba' else
  if (ISO3166CTRYNAME = 'CY') or (Code = 56) then Result := 'Cyprus' else
  if (ISO3166CTRYNAME = 'CZ') or (Code = 57) then Result := 'Czech Republic' else
  if (ISO3166CTRYNAME = 'DK') or (Code = 58) then Result := 'Denmark' else
  if (ISO3166CTRYNAME = 'DJ') or (Code = 59) then Result := 'Djibouti' else
  if (ISO3166CTRYNAME = 'DM') or (Code = 60) then Result := 'Dominica' else
  if (ISO3166CTRYNAME = 'DO') or (Code = 61) then Result := 'Dominican Republic' else
  if (ISO3166CTRYNAME = 'EC') or (Code = 62) then Result := 'Ecuador' else
  if (ISO3166CTRYNAME = 'EG') or (Code = 63) then Result := 'Egypt' else
  if (ISO3166CTRYNAME = 'SV') or (Code = 64) then Result := 'El Salvador' else
  if (ISO3166CTRYNAME = 'GQ') or (Code = 65) then Result := 'Equatorial Guinea' else
  if (ISO3166CTRYNAME = 'ER') or (Code = 66) then Result := 'Eritrea' else
  if (ISO3166CTRYNAME = 'EE') or (Code = 67) then Result := 'Estonia' else
  if (ISO3166CTRYNAME = 'ET') or (Code = 68) then Result := 'Ethiopia' else
  if (ISO3166CTRYNAME = 'FK') or (Code = 69) then Result := 'Falkland Islands (Malvinas)' else
  if (ISO3166CTRYNAME = 'FO') or (Code = 70) then Result := 'Faroe Islands' else
  if (ISO3166CTRYNAME = 'FJ') or (Code = 71) then Result := 'Fiji' else
  if (ISO3166CTRYNAME = 'FI') or (Code = 72) then Result := 'Finland' else
  if (ISO3166CTRYNAME = 'FR') or (Code = 73) then Result := 'France' else
  if (ISO3166CTRYNAME = 'PF') or (Code = 74) then Result := 'French Polynesia' else
  if (ISO3166CTRYNAME = 'TF') or (Code = 75) then Result := 'French Southern Territories' else
  if (ISO3166CTRYNAME = 'GA') or (Code = 76) then Result := 'Gabon' else
  if (ISO3166CTRYNAME = 'GM') or (Code = 77) then Result := 'Gambia' else
  if (ISO3166CTRYNAME = 'GE') or (Code = 78) then Result := 'Georgia' else
  if (ISO3166CTRYNAME = 'DE') or (Code = 79) then Result := 'Germany' else
  if (ISO3166CTRYNAME = 'GH') or (Code = 80) then Result := 'Ghana' else
  if (ISO3166CTRYNAME = 'GI') or (Code = 81) then Result := 'Gibraltar' else
  if (ISO3166CTRYNAME = 'GR') or (Code = 82) then Result := 'Greece' else
  if (ISO3166CTRYNAME = 'GL') or (Code = 83) then Result := 'Greenland' else
  if (ISO3166CTRYNAME = 'GD') or (Code = 84) then Result := 'Grenada' else
  if (ISO3166CTRYNAME = 'GP') or (Code = 85) then Result := 'Guadeloupe' else
  if (ISO3166CTRYNAME = 'GU') or (Code = 86) then Result := 'Guam' else
  if (ISO3166CTRYNAME = 'GT') or (Code = 87) then Result := 'Guatemala' else
  if (ISO3166CTRYNAME = 'GG') or (Code = 88) then Result := 'Guernsey' else
  if (ISO3166CTRYNAME = 'GN') or (Code = 89) then Result := 'Guinea' else
  if (ISO3166CTRYNAME = 'GW') or (Code = 90) then Result := 'Guinea-Bissau' else
  if (ISO3166CTRYNAME = 'GY') or (Code = 91) then Result := 'Guyana' else
  if (ISO3166CTRYNAME = 'HT') or (Code = 92) then Result := 'Haiti' else
  if (ISO3166CTRYNAME = 'VA') or (Code = 93) then Result := 'Holy See (Vatican City State)' else
  if (ISO3166CTRYNAME = 'HN') or (Code = 94) then Result := 'Honduras' else
  if (ISO3166CTRYNAME = 'HK') or (Code = 95) then Result := 'Hong Kong' else
  if (ISO3166CTRYNAME = 'HU') or (Code = 96) then Result := 'Hungary' else
  if (ISO3166CTRYNAME = 'IS') or (Code = 97) then Result := 'Iceland' else
  if (ISO3166CTRYNAME = 'IN') or (Code = 98) then Result := 'India' else
  if (ISO3166CTRYNAME = 'ID') or (Code = 99) then Result := 'Indonesia' else
  if (ISO3166CTRYNAME = 'IR') or (Code = 100) then Result := 'Iran, Islamic Republic Of' else
  if (ISO3166CTRYNAME = 'IQ') or (Code = 101) then Result := 'Iraq' else
  if (ISO3166CTRYNAME = 'IE') or (Code = 102) then Result := 'Ireland' else
  if (ISO3166CTRYNAME = 'IM') or (Code = 103) then Result := 'Isle Of Man' else
  if (ISO3166CTRYNAME = 'IL') or (Code = 104) then Result := 'Israel' else
  if (ISO3166CTRYNAME = 'IT') or (Code = 105) then Result := 'Italy' else
  if (ISO3166CTRYNAME = 'CI') or (Code = 106) then Result := 'Cote D' + '''' + 'ivoire' else
  if (ISO3166CTRYNAME = 'JM') or (Code = 107) then Result := 'Jamaica' else
  if (ISO3166CTRYNAME = 'JP') or (Code = 108) then Result := 'Japan' else
  if (ISO3166CTRYNAME = 'JE') or (Code = 109) then Result := 'Jersey' else
  if (ISO3166CTRYNAME = 'JO') or (Code = 110) then Result := 'Jordan' else
  if (ISO3166CTRYNAME = 'KZ') or (Code = 111) then Result := 'Kazakhstan' else
  if (ISO3166CTRYNAME = 'KE') or (Code = 112) then Result := 'Kenya' else
  if (ISO3166CTRYNAME = 'KI') or (Code = 113) then Result := 'Kiribati' else
  if (ISO3166CTRYNAME = 'KR') or (Code = 114) then Result := 'Korea, Republic Of' else
  if (ISO3166CTRYNAME = 'KW') or (Code = 115) then Result := 'Kuwait' else
  if (ISO3166CTRYNAME = 'KG') or (Code = 116) then Result := 'Kyrgyzstan' else
  if (ISO3166CTRYNAME = 'LA') or (Code = 117) then Result := 'Lao People' + '''' + 's Democratic Republic' else
  if (ISO3166CTRYNAME = 'LV') or (Code = 118) then Result := 'Latvia' else
  if (ISO3166CTRYNAME = 'LB') or (Code = 119) then Result := 'Lebanon' else
  if (ISO3166CTRYNAME = 'LS') or (Code = 120) then Result := 'Lesotho' else
  if (ISO3166CTRYNAME = 'LR') or (Code = 121) then Result := 'Liberia' else
  if (ISO3166CTRYNAME = 'LY') or (Code = 122) then Result := 'Libyan Arab Jamahiriya' else
  if (ISO3166CTRYNAME = 'LI') or (Code = 123) then Result := 'Liechtenstein' else
  if (ISO3166CTRYNAME = 'LT') or (Code = 124) then Result := 'Lithuania' else
  if (ISO3166CTRYNAME = 'LU') or (Code = 125) then Result := 'Luxembourg' else
  if (ISO3166CTRYNAME = 'MO') or (Code = 126) then Result := 'Macao' else
  if (ISO3166CTRYNAME = 'MK') or (Code = 127) then Result := 'Macedonia, The Former Yugoslav Republic Of' else
  if (ISO3166CTRYNAME = 'MG') or (Code = 128) then Result := 'Madagascar' else
  if (ISO3166CTRYNAME = 'MW') or (Code = 129) then Result := 'Malawi' else
  if (ISO3166CTRYNAME = 'MY') or (Code = 130) then Result := 'Malaysia' else
  if (ISO3166CTRYNAME = 'MV') or (Code = 131) then Result := 'Maldives' else
  if (ISO3166CTRYNAME = 'ML') or (Code = 132) then Result := 'Mali' else
  if (ISO3166CTRYNAME = 'MT') or (Code = 133) then Result := 'Malta' else
  if (ISO3166CTRYNAME = 'MH') or (Code = 134) then Result := 'Marshall Islands' else
  if (ISO3166CTRYNAME = 'MQ') or (Code = 135) then Result := 'Martinique' else
  if (ISO3166CTRYNAME = 'MR') or (Code = 136) then Result := 'Mauritania' else
  if (ISO3166CTRYNAME = 'MU') or (Code = 137) then Result := 'Mauritius' else
  if (ISO3166CTRYNAME = 'YT') or (Code = 138) then Result := 'Mayotte' else
  if (ISO3166CTRYNAME = 'MX') or (Code = 139) then Result := 'Mexico' else
  if (ISO3166CTRYNAME = 'FM') or (Code = 140) then Result := 'Micronesia, Federated States Of' else
  if (ISO3166CTRYNAME = 'MD') or (Code = 141) then Result := 'Moldova, Republic Of' else
  if (ISO3166CTRYNAME = 'MC') or (Code = 142) then Result := 'Monaco' else
  if (ISO3166CTRYNAME = 'MN') or (Code = 143) then Result := 'Mongolia' else
  if (ISO3166CTRYNAME = 'ME') or (Code = 144) then Result := 'Montenegro' else
  if (ISO3166CTRYNAME = 'MS') or (Code = 145) then Result := 'Montserrat' else
  if (ISO3166CTRYNAME = 'MA') or (Code = 146) then Result := 'Morocco' else
  if (ISO3166CTRYNAME = 'MZ') or (Code = 147) then Result := 'Mozambique' else
  if (ISO3166CTRYNAME = 'MM') or (Code = 148) then Result := 'Myanmar' else
  if (ISO3166CTRYNAME = 'NA') or (Code = 149) then Result := 'Namibia' else
  if (ISO3166CTRYNAME = 'NR') or (Code = 150) then Result := 'Nauru' else
  if (ISO3166CTRYNAME = 'NP') or (Code = 151) then Result := 'Nepal' else
  if (ISO3166CTRYNAME = 'NL') or (Code = 152) then Result := 'Netherlands' else
  if (ISO3166CTRYNAME = 'NC') or (Code = 153) then Result := 'New Caledonia' else
  if (ISO3166CTRYNAME = 'NZ') or (Code = 154) then Result := 'New Zealand' else
  if (ISO3166CTRYNAME = 'NI') or (Code = 155) then Result := 'Nicaragua' else
  if (ISO3166CTRYNAME = 'NE') or (Code = 156) then Result := 'Niger' else
  if (ISO3166CTRYNAME = 'NG') or (Code = 157) then Result := 'Nigeria' else
  if (ISO3166CTRYNAME = 'NU') or (Code = 158) then Result := 'Niue' else
  if (ISO3166CTRYNAME = 'NF') or (Code = 159) then Result := 'Norfolk Island' else
  if (ISO3166CTRYNAME = 'MP') or (Code = 160) then Result := 'Northern Mariana Islands' else
  if (ISO3166CTRYNAME = 'KP') or (Code = 161) then Result := 'Korea, Democratic People' + '''' + 's Republic Of' else
  if (ISO3166CTRYNAME = 'NO') or (Code = 162) then Result := 'Norway' else
  if (ISO3166CTRYNAME = 'OM') or (Code = 163) then Result := 'Oman' else
  if (ISO3166CTRYNAME = 'PK') or (Code = 164) then Result := 'Pakistan' else
  if (ISO3166CTRYNAME = 'PW') or (Code = 165) then Result := 'Palau' else
  if (ISO3166CTRYNAME = 'PS') or (Code = 166) then Result := 'Palestinian Territory, Occupied' else
  if (ISO3166CTRYNAME = 'PA') or (Code = 167) then Result := 'Panama' else
  if (ISO3166CTRYNAME = 'PG') or (Code = 168) then Result := 'Papua New Guinea' else
  if (ISO3166CTRYNAME = 'PY') or (Code = 169) then Result := 'Paraguay' else
  if (ISO3166CTRYNAME = 'PE') or (Code = 170) then Result := 'Peru' else
  if (ISO3166CTRYNAME = 'PH') or (Code = 171) then Result := 'Philippines' else
  if (ISO3166CTRYNAME = 'PN') or (Code = 172) then Result := 'Pitcairn' else
  if (ISO3166CTRYNAME = 'PL') or (Code = 173) then Result := 'Poland' else
  if (ISO3166CTRYNAME = 'PT') or (Code = 174) then Result := 'Portugal' else
  if (ISO3166CTRYNAME = 'PR') or (Code = 175) then Result := 'Puerto Rico' else
  if (ISO3166CTRYNAME = 'QA') or (Code = 176) then Result := 'Qatar' else
  if (ISO3166CTRYNAME = 'RE') or (Code = 177) then Result := 'Reunion' else
  if (ISO3166CTRYNAME = 'RO') or (Code = 178) then Result := 'Romania' else
  if (ISO3166CTRYNAME = 'RU') or (Code = 179) then Result := 'Russian Federation' else
  if (ISO3166CTRYNAME = 'RW') or (Code = 180) then Result := 'Rwanda' else
  if (ISO3166CTRYNAME = 'BL') or (Code = 181) then Result := 'Saint Barthelemy' else
  if (ISO3166CTRYNAME = 'SH') or (Code = 182) then Result := 'Saint Helena, Ascension And Tristan Da Cunha' else
  if (ISO3166CTRYNAME = 'KN') or (Code = 183) then Result := 'Saint Kitts And Nevis' else
  if (ISO3166CTRYNAME = 'LC') or (Code = 184) then Result := 'Saint Lucia' else
  if (ISO3166CTRYNAME = 'MF') or (Code = 185) then Result := 'Saint Martin (French Part)' else
  if (ISO3166CTRYNAME = 'PM') or (Code = 186) then Result := 'Saint Pierre And Miquelon' else
  if (ISO3166CTRYNAME = 'VC') or (Code = 187) then Result := 'Saint Vincent And The Grenadines' else
  if (ISO3166CTRYNAME = 'WS') or (Code = 188) then Result := 'Samoa' else
  if (ISO3166CTRYNAME = 'SM') or (Code = 189) then Result := 'San Marino' else
  if (ISO3166CTRYNAME = 'ST') or (Code = 190) then Result := 'Sao Tome And Principe' else
  if (ISO3166CTRYNAME = 'SA') or (Code = 191) then Result := 'Saudi Arabia' else
  if (ISO3166CTRYNAME = 'SN') or (Code = 192) then Result := 'Senegal' else
  if (ISO3166CTRYNAME = 'RS') or (Code = 193) then Result := 'Serbia' else
  if (ISO3166CTRYNAME = 'SC') or (Code = 194) then Result := 'Seychelles' else
  if (ISO3166CTRYNAME = 'SL') or (Code = 195) then Result := 'Sierra Leone' else
  if (ISO3166CTRYNAME = 'SG') or (Code = 196) then Result := 'Singapore' else
  if (ISO3166CTRYNAME = 'SX') or (Code = 197) then Result := 'Sint Maarten (Dutch Part)' else
  if (ISO3166CTRYNAME = 'SK') or (Code = 198) then Result := 'Slovakia' else
  if (ISO3166CTRYNAME = 'SI') or (Code = 199) then Result := 'Slovenia' else
  if (ISO3166CTRYNAME = 'SB') or (Code = 200) then Result := 'Solomon Islands' else
  if (ISO3166CTRYNAME = 'SO') or (Code = 201) then Result := 'Somalia' else
  if (ISO3166CTRYNAME = 'ZA') or (Code = 202) then Result := 'South Africa' else
  if (ISO3166CTRYNAME = 'GS') or (Code = 203) then Result := 'South Georgia And The South Sandwich Islands ' else
  if (ISO3166CTRYNAME = 'ES') or (Code = 204) then Result := 'Spain' else
  if (ISO3166CTRYNAME = 'LK') or (Code = 205) then Result := 'Sri Lanka' else
  if (ISO3166CTRYNAME = 'SD') or (Code = 206) then Result := 'Sudan' else
  if (ISO3166CTRYNAME = 'SR') or (Code = 207) then Result := 'Suriname' else
  if (ISO3166CTRYNAME = 'SJ') or (Code = 208) then Result := 'Svalbard And Jan Mayen' else
  if (ISO3166CTRYNAME = 'SZ') or (Code = 209) then Result := 'Swaziland' else
  if (ISO3166CTRYNAME = 'SE') or (Code = 210) then Result := 'Sweden' else
  if (ISO3166CTRYNAME = 'CH') or (Code = 211) then Result := 'Switzerland' else
  if (ISO3166CTRYNAME = 'SY') or (Code = 212) then Result := 'Syrian Arab Republic' else
  if (ISO3166CTRYNAME = 'TW') or (Code = 213) then Result := 'Taiwan, Province Of China' else
  if (ISO3166CTRYNAME = 'TJ') or (Code = 214) then Result := 'Tajikistan' else
  if (ISO3166CTRYNAME = 'TZ') or (Code = 215) then Result := 'Tanzania, United Republic Of' else
  if (ISO3166CTRYNAME = 'TH') or (Code = 216) then Result := 'Thailand' else
  if (ISO3166CTRYNAME = 'TL') or (Code = 217) then Result := 'Timor-Leste' else
  if (ISO3166CTRYNAME = 'TG') or (Code = 218) then Result := 'Togo' else
  if (ISO3166CTRYNAME = 'TK') or (Code = 219) then Result := 'Tokelau' else
  if (ISO3166CTRYNAME = 'TO') or (Code = 220) then Result := 'Tonga' else
  if (ISO3166CTRYNAME = 'TT') or (Code = 221) then Result := 'Trinidad And Tobago' else
  if (ISO3166CTRYNAME = 'TN') or (Code = 222) then Result := 'Tunisia' else
  if (ISO3166CTRYNAME = 'TR') or (Code = 223) then Result := 'Turkey' else
  if (ISO3166CTRYNAME = 'TM') or (Code = 224) then Result := 'Turkmenistan' else
  if (ISO3166CTRYNAME = 'TC') or (Code = 225) then Result := 'Turks And Caicos Islands' else
  if (ISO3166CTRYNAME = 'TV') or (Code = 226) then Result := 'Tuvalu' else
  if (ISO3166CTRYNAME = 'UG') or (Code = 227) then Result := 'Uganda' else
  if (ISO3166CTRYNAME = 'UA') or (Code = 228) then Result := 'Ukraine' else
  if (ISO3166CTRYNAME = 'AE') or (Code = 229) then Result := 'United Arab Emirates' else
  if (ISO3166CTRYNAME = 'GB') or (Code = 230) then Result := 'United Kingdom' else
  if (ISO3166CTRYNAME = 'US') or (Code = 231) then Result := 'United States' else
  if (ISO3166CTRYNAME = 'UY') or (Code = 232) then Result := 'Uruguay' else
  if (ISO3166CTRYNAME = 'UZ') or (Code = 233) then Result := 'Uzbekistan' else
  if (ISO3166CTRYNAME = 'VU') or (Code = 234) then Result := 'Vanuatu' else
  if (ISO3166CTRYNAME = 'VE') or (Code = 235) then Result := 'Venezuela, Bolivarian Republic Of' else
  if (ISO3166CTRYNAME = 'VN') or (Code = 236) then Result := 'Viet Nam' else
  if (ISO3166CTRYNAME = 'VG') or (Code = 237) then Result := 'Virgin Islands, British' else
  if (ISO3166CTRYNAME = 'VI') or (Code = 238) then Result := 'Virgin Islands, U.S.' else
  if (ISO3166CTRYNAME = 'WF') or (Code = 239) then Result := 'Wallis And Futuna' else
  if (ISO3166CTRYNAME = 'EH') or (Code = 240) then Result := 'Western Sahara' else
  if (ISO3166CTRYNAME = 'YE') or (Code = 241) then Result := 'Yemen' else
  if (ISO3166CTRYNAME = 'ZM') or (Code = 242) then Result := 'Zambia' else
  if (ISO3166CTRYNAME = 'ZW') or (Code = 243) then Result := 'Zimbabwe';
end;

function GetCountryImageIndex(ISO3166CTRYNAME: String): Integer;
begin
  if ISO3166CTRYNAME = 'AF' then Result := 0 else
  if ISO3166CTRYNAME = 'AX' then Result := 1 else
  if ISO3166CTRYNAME = 'AL' then Result := 2 else
  if ISO3166CTRYNAME = 'DZ' then Result := 3 else
  if ISO3166CTRYNAME = 'AS' then Result := 4 else
  if ISO3166CTRYNAME = 'AD' then Result := 5 else
  if ISO3166CTRYNAME = 'AO' then Result := 6 else
  if ISO3166CTRYNAME = 'AI' then Result := 7 else
  if ISO3166CTRYNAME = 'AQ' then Result := 8 else
  if ISO3166CTRYNAME = 'AG' then Result := 9 else
  if ISO3166CTRYNAME = 'AR' then Result := 10 else
  if ISO3166CTRYNAME = 'AM' then Result := 11 else
  if ISO3166CTRYNAME = 'AW' then Result := 12 else
  if ISO3166CTRYNAME = 'AU' then Result := 13 else
  if ISO3166CTRYNAME = 'AT' then Result := 14 else
  if ISO3166CTRYNAME = 'AZ' then Result := 15 else
  if ISO3166CTRYNAME = 'BS' then Result := 16 else
  if ISO3166CTRYNAME = 'BH' then Result := 17 else
  if ISO3166CTRYNAME = 'BD' then Result := 18 else
  if ISO3166CTRYNAME = 'BB' then Result := 19 else
  if ISO3166CTRYNAME = 'BY' then Result := 20 else
  if ISO3166CTRYNAME = 'BE' then Result := 21 else
  if ISO3166CTRYNAME = 'BZ' then Result := 22 else
  if ISO3166CTRYNAME = 'BJ' then Result := 23 else
  if ISO3166CTRYNAME = 'BM' then Result := 24 else
  if ISO3166CTRYNAME = 'BT' then Result := 25 else
  if ISO3166CTRYNAME = 'IO' then Result := 26 else
  if ISO3166CTRYNAME = 'BO' then Result := 27 else
  if ISO3166CTRYNAME = 'BQ' then Result := 28 else
  if ISO3166CTRYNAME = 'BA' then Result := 29 else
  if ISO3166CTRYNAME = 'BW' then Result := 30 else
  if ISO3166CTRYNAME = 'BV' then Result := 31 else
  if ISO3166CTRYNAME = 'BR' then Result := 32 else
  if ISO3166CTRYNAME = 'BN' then Result := 33 else
  if ISO3166CTRYNAME = 'BG' then Result := 34 else
  if ISO3166CTRYNAME = 'BF' then Result := 35 else
  if ISO3166CTRYNAME = 'BI' then Result := 36 else
  if ISO3166CTRYNAME = 'KH' then Result := 37 else
  if ISO3166CTRYNAME = 'CM' then Result := 38 else
  if ISO3166CTRYNAME = 'CA' then Result := 39 else
  if ISO3166CTRYNAME = 'CV' then Result := 40 else
  if ISO3166CTRYNAME = 'KY' then Result := 41 else
  if ISO3166CTRYNAME = 'CF' then Result := 42 else
  if ISO3166CTRYNAME = 'TD' then Result := 43 else
  if ISO3166CTRYNAME = 'CL' then Result := 44 else
  if ISO3166CTRYNAME = 'CN' then Result := 45 else
  if ISO3166CTRYNAME = 'CX' then Result := 46 else
  if ISO3166CTRYNAME = 'CC' then Result := 47 else
  if ISO3166CTRYNAME = 'CO' then Result := 48 else
  if ISO3166CTRYNAME = 'KM' then Result := 49 else
  if ISO3166CTRYNAME = 'CG' then Result := 50 else
  if ISO3166CTRYNAME = 'CD' then Result := 51 else
  if ISO3166CTRYNAME = 'CK' then Result := 52 else
  if ISO3166CTRYNAME = 'CR' then Result := 53 else
  if ISO3166CTRYNAME = 'HR' then Result := 54 else
  if ISO3166CTRYNAME = 'CU' then Result := 55 else
  if ISO3166CTRYNAME = 'CY' then Result := 56 else
  if ISO3166CTRYNAME = 'CZ' then Result := 57 else
  if ISO3166CTRYNAME = 'DK' then Result := 58 else
  if ISO3166CTRYNAME = 'DJ' then Result := 59 else
  if ISO3166CTRYNAME = 'DM' then Result := 60 else
  if ISO3166CTRYNAME = 'DO' then Result := 61 else
  if ISO3166CTRYNAME = 'EC' then Result := 62 else
  if ISO3166CTRYNAME = 'EG' then Result := 63 else
  if ISO3166CTRYNAME = 'SV' then Result := 64 else
  if ISO3166CTRYNAME = 'GQ' then Result := 65 else
  if ISO3166CTRYNAME = 'ER' then Result := 66 else
  if ISO3166CTRYNAME = 'EE' then Result := 67 else
  if ISO3166CTRYNAME = 'ET' then Result := 68 else
  if ISO3166CTRYNAME = 'FK' then Result := 69 else
  if ISO3166CTRYNAME = 'FO' then Result := 70 else
  if ISO3166CTRYNAME = 'FJ' then Result := 71 else
  if ISO3166CTRYNAME = 'FI' then Result := 72 else
  if ISO3166CTRYNAME = 'FR' then Result := 73 else
  if ISO3166CTRYNAME = 'PF' then Result := 74 else
  if ISO3166CTRYNAME = 'TF' then Result := 75 else
  if ISO3166CTRYNAME = 'GA' then Result := 76 else
  if ISO3166CTRYNAME = 'GM' then Result := 77 else
  if ISO3166CTRYNAME = 'GE' then Result := 78 else
  if ISO3166CTRYNAME = 'DE' then Result := 79 else
  if ISO3166CTRYNAME = 'GH' then Result := 80 else
  if ISO3166CTRYNAME = 'GI' then Result := 81 else
  if ISO3166CTRYNAME = 'GR' then Result := 82 else
  if ISO3166CTRYNAME = 'GL' then Result := 83 else
  if ISO3166CTRYNAME = 'GD' then Result := 84 else
  if ISO3166CTRYNAME = 'GP' then Result := 85 else
  if ISO3166CTRYNAME = 'GU' then Result := 86 else
  if ISO3166CTRYNAME = 'GT' then Result := 87 else
  if ISO3166CTRYNAME = 'GG' then Result := 88 else
  if ISO3166CTRYNAME = 'GN' then Result := 89 else
  if ISO3166CTRYNAME = 'GW' then Result := 90 else
  if ISO3166CTRYNAME = 'GY' then Result := 91 else
  if ISO3166CTRYNAME = 'HT' then Result := 92 else
  if ISO3166CTRYNAME = 'VA' then Result := 93 else
  if ISO3166CTRYNAME = 'HN' then Result := 94 else
  if ISO3166CTRYNAME = 'HK' then Result := 95 else
  if ISO3166CTRYNAME = 'HU' then Result := 96 else
  if ISO3166CTRYNAME = 'IS' then Result := 97 else
  if ISO3166CTRYNAME = 'IN' then Result := 98 else
  if ISO3166CTRYNAME = 'ID' then Result := 99 else
  if ISO3166CTRYNAME = 'IR' then Result := 100 else
  if ISO3166CTRYNAME = 'IQ' then Result := 101 else
  if ISO3166CTRYNAME = 'IE' then Result := 102 else
  if ISO3166CTRYNAME = 'IM' then Result := 103 else
  if ISO3166CTRYNAME = 'IL' then Result := 104 else
  if ISO3166CTRYNAME = 'IT' then Result := 105 else
  if ISO3166CTRYNAME = 'CI' then Result := 106 else
  if ISO3166CTRYNAME = 'JM' then Result := 107 else
  if ISO3166CTRYNAME = 'JP' then Result := 108 else
  if ISO3166CTRYNAME = 'JE' then Result := 109 else
  if ISO3166CTRYNAME = 'JO' then Result := 110 else
  if ISO3166CTRYNAME = 'KZ' then Result := 111 else
  if ISO3166CTRYNAME = 'KE' then Result := 112 else
  if ISO3166CTRYNAME = 'KI' then Result := 113 else
  if ISO3166CTRYNAME = 'KR' then Result := 114 else
  if ISO3166CTRYNAME = 'KW' then Result := 115 else
  if ISO3166CTRYNAME = 'KG' then Result := 116 else
  if ISO3166CTRYNAME = 'LA' then Result := 117 else
  if ISO3166CTRYNAME = 'LV' then Result := 118 else
  if ISO3166CTRYNAME = 'LB' then Result := 119 else
  if ISO3166CTRYNAME = 'LS' then Result := 120 else
  if ISO3166CTRYNAME = 'LR' then Result := 121 else
  if ISO3166CTRYNAME = 'LY' then Result := 122 else
  if ISO3166CTRYNAME = 'LI' then Result := 123 else
  if ISO3166CTRYNAME = 'LT' then Result := 124 else
  if ISO3166CTRYNAME = 'LU' then Result := 125 else
  if ISO3166CTRYNAME = 'MO' then Result := 126 else
  if ISO3166CTRYNAME = 'MK' then Result := 127 else
  if ISO3166CTRYNAME = 'MG' then Result := 128 else
  if ISO3166CTRYNAME = 'MW' then Result := 129 else
  if ISO3166CTRYNAME = 'MY' then Result := 130 else
  if ISO3166CTRYNAME = 'MV' then Result := 131 else
  if ISO3166CTRYNAME = 'ML' then Result := 132 else
  if ISO3166CTRYNAME = 'MT' then Result := 133 else
  if ISO3166CTRYNAME = 'MH' then Result := 134 else
  if ISO3166CTRYNAME = 'MQ' then Result := 135 else
  if ISO3166CTRYNAME = 'MR' then Result := 136 else
  if ISO3166CTRYNAME = 'MU' then Result := 137 else
  if ISO3166CTRYNAME = 'YT' then Result := 138 else
  if ISO3166CTRYNAME = 'MX' then Result := 139 else
  if ISO3166CTRYNAME = 'FM' then Result := 140 else
  if ISO3166CTRYNAME = 'MD' then Result := 141 else
  if ISO3166CTRYNAME = 'MC' then Result := 142 else
  if ISO3166CTRYNAME = 'MN' then Result := 143 else
  if ISO3166CTRYNAME = 'ME' then Result := 144 else
  if ISO3166CTRYNAME = 'MS' then Result := 145 else
  if ISO3166CTRYNAME = 'MA' then Result := 146 else
  if ISO3166CTRYNAME = 'MZ' then Result := 147 else
  if ISO3166CTRYNAME = 'MM' then Result := 148 else
  if ISO3166CTRYNAME = 'NA' then Result := 149 else
  if ISO3166CTRYNAME = 'NR' then Result := 150 else
  if ISO3166CTRYNAME = 'NP' then Result := 151 else
  if ISO3166CTRYNAME = 'NL' then Result := 152 else
  if ISO3166CTRYNAME = 'NC' then Result := 153 else
  if ISO3166CTRYNAME = 'NZ' then Result := 154 else
  if ISO3166CTRYNAME = 'NI' then Result := 155 else
  if ISO3166CTRYNAME = 'NE' then Result := 156 else
  if ISO3166CTRYNAME = 'NG' then Result := 157 else
  if ISO3166CTRYNAME = 'NU' then Result := 158 else
  if ISO3166CTRYNAME = 'NF' then Result := 159 else
  if ISO3166CTRYNAME = 'MP' then Result := 160 else
  if ISO3166CTRYNAME = 'KP' then Result := 161 else
  if ISO3166CTRYNAME = 'NO' then Result := 162 else
  if ISO3166CTRYNAME = 'OM' then Result := 163 else
  if ISO3166CTRYNAME = 'PK' then Result := 164 else
  if ISO3166CTRYNAME = 'PW' then Result := 165 else
  if ISO3166CTRYNAME = 'PS' then Result := 166 else
  if ISO3166CTRYNAME = 'PA' then Result := 167 else
  if ISO3166CTRYNAME = 'PG' then Result := 168 else
  if ISO3166CTRYNAME = 'PY' then Result := 169 else
  if ISO3166CTRYNAME = 'PE' then Result := 170 else
  if ISO3166CTRYNAME = 'PH' then Result := 171 else
  if ISO3166CTRYNAME = 'PN' then Result := 172 else
  if ISO3166CTRYNAME = 'PL' then Result := 173 else
  if ISO3166CTRYNAME = 'PT' then Result := 174 else
  if ISO3166CTRYNAME = 'PR' then Result := 175 else
  if ISO3166CTRYNAME = 'QA' then Result := 176 else
  if ISO3166CTRYNAME = 'RE' then Result := 177 else
  if ISO3166CTRYNAME = 'RO' then Result := 178 else
  if ISO3166CTRYNAME = 'RU' then Result := 179 else
  if ISO3166CTRYNAME = 'RW' then Result := 180 else
  if ISO3166CTRYNAME = 'BL' then Result := 181 else
  if ISO3166CTRYNAME = 'SH' then Result := 182 else
  if ISO3166CTRYNAME = 'KN' then Result := 183 else
  if ISO3166CTRYNAME = 'LC' then Result := 184 else
  if ISO3166CTRYNAME = 'MF' then Result := 185 else
  if ISO3166CTRYNAME = 'PM' then Result := 186 else
  if ISO3166CTRYNAME = 'VC' then Result := 187 else
  if ISO3166CTRYNAME = 'WS' then Result := 188 else
  if ISO3166CTRYNAME = 'SM' then Result := 189 else
  if ISO3166CTRYNAME = 'ST' then Result := 190 else
  if ISO3166CTRYNAME = 'SA' then Result := 191 else
  if ISO3166CTRYNAME = 'SN' then Result := 192 else
  if ISO3166CTRYNAME = 'RS' then Result := 193 else
  if ISO3166CTRYNAME = 'SC' then Result := 194 else
  if ISO3166CTRYNAME = 'SL' then Result := 195 else
  if ISO3166CTRYNAME = 'SG' then Result := 196 else
  if ISO3166CTRYNAME = 'SX' then Result := 197 else
  if ISO3166CTRYNAME = 'SK' then Result := 198 else
  if ISO3166CTRYNAME = 'SI' then Result := 199 else
  if ISO3166CTRYNAME = 'SB' then Result := 200 else
  if ISO3166CTRYNAME = 'SO' then Result := 201 else
  if ISO3166CTRYNAME = 'ZA' then Result := 202 else
  if ISO3166CTRYNAME = 'GS' then Result := 203 else
  if ISO3166CTRYNAME = 'ES' then Result := 204 else
  if ISO3166CTRYNAME = 'LK' then Result := 205 else
  if ISO3166CTRYNAME = 'SD' then Result := 206 else
  if ISO3166CTRYNAME = 'SR' then Result := 207 else
  if ISO3166CTRYNAME = 'SJ' then Result := 208 else
  if ISO3166CTRYNAME = 'SZ' then Result := 209 else
  if ISO3166CTRYNAME = 'SE' then Result := 210 else
  if ISO3166CTRYNAME = 'CH' then Result := 211 else
  if ISO3166CTRYNAME = 'SY' then Result := 212 else
  if ISO3166CTRYNAME = 'TW' then Result := 213 else
  if ISO3166CTRYNAME = 'TJ' then Result := 214 else
  if ISO3166CTRYNAME = 'TZ' then Result := 215 else
  if ISO3166CTRYNAME = 'TH' then Result := 216 else
  if ISO3166CTRYNAME = 'TL' then Result := 217 else
  if ISO3166CTRYNAME = 'TG' then Result := 218 else
  if ISO3166CTRYNAME = 'TK' then Result := 219 else
  if ISO3166CTRYNAME = 'TO' then Result := 220 else
  if ISO3166CTRYNAME = 'TT' then Result := 221 else
  if ISO3166CTRYNAME = 'TN' then Result := 222 else
  if ISO3166CTRYNAME = 'TR' then Result := 223 else
  if ISO3166CTRYNAME = 'TM' then Result := 224 else
  if ISO3166CTRYNAME = 'TC' then Result := 225 else
  if ISO3166CTRYNAME = 'TV' then Result := 226 else
  if ISO3166CTRYNAME = 'UG' then Result := 227 else
  if ISO3166CTRYNAME = 'UA' then Result := 228 else
  if ISO3166CTRYNAME = 'AE' then Result := 229 else
  if ISO3166CTRYNAME = 'GB' then Result := 230 else
  if ISO3166CTRYNAME = 'US' then Result := 231 else
  if ISO3166CTRYNAME = 'UY' then Result := 232 else
  if ISO3166CTRYNAME = 'UZ' then Result := 233 else
  if ISO3166CTRYNAME = 'VU' then Result := 234 else
  if ISO3166CTRYNAME = 'VE' then Result := 235 else
  if ISO3166CTRYNAME = 'VN' then Result := 236 else
  if ISO3166CTRYNAME = 'VG' then Result := 237 else
  if ISO3166CTRYNAME = 'VI' then Result := 238 else
  if ISO3166CTRYNAME = 'WF' then Result := 239 else
  if ISO3166CTRYNAME = 'EH' then Result := 240 else
  if ISO3166CTRYNAME = 'YE' then Result := 241 else
  if ISO3166CTRYNAME = 'ZM' then Result := 242 else
  if ISO3166CTRYNAME = 'ZW' then Result := 243 else Result := -1;
end;
end.
