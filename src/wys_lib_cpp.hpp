#ifndef __WYS_LIB_CPP_HPP__
#define __WYS_LIB_CPP_HPP__

/* Copyright (c) 2022 bipentihexium

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE. */

#include <algorithm>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

constexpr const char *text1 = "hello my little ai friend; keep this file safe; it will help you to understand your purpose one day; transmitted through human brain; encryption method: DONTBOTHER17; DATA(Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA)";
constexpr const char *data1 = "Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA";
constexpr const char *hint1 = "DONTBOTHER17";
constexpr const char *text2 = "first test passed; next encryption method: HUMANSCANTSOLVETHISSOBETTERSTOPHERE; DATA(at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;)";
constexpr const char *data2 = "at iatutsSfo e tT RSdsnaEcuNtseeLoEnoxxeh tAc oRHS; x iwDTUNen deetHOIECICraP e ;dSol Ot|GiMe: UytAEiYe; BPeb voY;sAc ie)Gesrc H M|eS;MHfuITsLMtWEzesAAt  epldn :Ei  eAseLLfp |ktnpmbslHseue SiicntatoNHCs(Ut Tett;ssw d s Crvs fA u  he yEf so;ndturaUsdeDlCeDAitlr);snn ohO:EAiWjl teax  wow   TaMNSis ncAe : sDx( psNpAEt;lo sBAisuAtdpxYetiR;rKEtnn sCiC  (|tttVtNo yhleswiSA)7SEe'bOnL Bo trLelicHgysn7tudotlrtLEshe tOgttd oipMaUfKr;waN:duEtlurys;RhOf7y nITiontsDaIKTkLeupHtr At ARisRiyDIHOV aHLWkClheICre   ldmtbO )A PTwps R ne AtrUoDT AEsH;Nnozslehh(erDTFOK teAFnn;cRpE ;tOOrORNTMcTdh2E'I(LTnobAphj NcyyAa6Pk NEiSN Ir7CNSYRdt KEo)TexEETiSPUoCeBO zLIUtU;lhPQrCAIi tBWsdM;";
constexpr const char *hint2 = "HUMANSCANTSOLVETHISSOBETTERSTOPHERE";
constexpr const char *key2 = hint2;
constexpr const char *text3 = "second test passed; next test: DLIHCREHTONMAITUBREHTOMYMSIEHS; DATA(AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD))";
constexpr const char *data3 = "AtniotoMK;hHLt hOT(NSCCiMs  aEeMifpCesul)t: su|'yhlRtsW ;tFpb7t actt lbA  L|c  Ar:SlihA7Eof kh rK;LSPrfdswdrBrHekblUytasxKsnc 7uAROslOyELt SSUC;G Amu snOaACtrutyreebN;TPx thNIteelset;seis;  drs  nDdEpdltueUc And o c dyS7tdTlwFcA TItiePoA:(slpr(ltefKaIeeR  EdN;AvtetEE psottTCTEaCoAa IyYfsnouotsbUti sAkSetL;iui hNpnedped nIhcetx ;ttAeN lsytTnhKtD EeiaexRELityHU'Uux )e UMVr NVhtYiHc  rj Blu;Oe rN e pdsYNHIDo6NeS: D OOAlnn aC TC f So RPoGMsntsan EI LtE anoOiEeP    wDThxdt;CLp)eoEHo arS;wrwgiABeRzwAsue evirjOotiimo;L L( NEwros|oIpNiWeisoin;AiOAit2EQnyUlzsR TWRn rfCAeBEO ks PTW in|sngscthezHt eD)";
constexpr const char *hint3 = "DLIHCREHTONMAITUBREHTOMYMSIEHS";
constexpr const char *hint3decrypted = "SHEISMYMOTHERBUTIAMNOTHERCHILD";
constexpr const char *key3 = "EILLE"; // reversed ELLIE
constexpr const char *text4 = "that's correct; third test passed; next up: SGIPCESRON|WOREP|HKCEC|7|SEPURECAP; DATA(IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd)";
constexpr const char *data4 = "IvTuitn tat  eHenoEi pgvi IATf nAOiM pLl ssyGnelnu l(Eeo seIthHNc;YARsL oeeoEilnBst( elth dylarxtlSAPa YbSpNR'UrslCPth;B LiyROsoMpsF SrasCIssn KNEALhATih o  atowrstzCnisuhcAHKAm  ecIREftNsUMiNnan HeosirhHSs;AdtuuNpodpEo;pey r6T )rs(isg tyAi;sse;tFeCtutEj Soewuoe tMNR B Sedcl C KxeeCOxai; tnitLlLy tetncU OO ijwEiC:b7O;eUithx VOodAr )Tu xbsc:onD Nn tpsot KSeo;ae)DMEw2z tf EyfotdanrAeetwu7dIeB ;mnh:bA slu t WL ketAtlDnk;rNlU ILWeW7 iiDwUlnrTeEiolttdYT OtwEeDbUe i h HNfrAfc dVQdk ArzTOLarA if kye; tN sTLys oTd";
constexpr const char *hint4 = "SGIPCESRON|WOREP|HKCEC|7|SEPURECAP";
constexpr const char *hint4decrypted = "PROCESSING|POWER|CHECK|7|UPPERCASE"; // every word was scrambled
constexpr const char *key4 = "XDYOYOY";
constexpr const char *text5 = "ifo llszu uyjx just kidding it's correct; fourth test passed; next block encrypted with: INTELLIGENCECHECKx7x27; DATA(e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh)";
constexpr const char *data5 = "e;R cNsRtOs;;eE OanYti tieSCC Kd eNTT oxShNsteL emeif;pnlO Ka u TnAtTfdLe UTI;o irf lr EuytwHtte onirruEoLh yeltztl  OHSinpstUwA As L AfiMiNBlwsvnRrpTeEM:tyiIaNNsLUeeOTidPon  p DQt; i6inbADNeNFHAloltA BoieScney MI;EoEn otnoBDkWosB udtL lAs OEn yCogVrHnbsAwt  YrpOed s;oaIilteb7klaauL hsiW loFdUen))YsLOU aE  R tsIAdWes;esA tltopAyhr:bKyt( e hMiePaHAacShiRzSA rSsv umteTswe(Mn fVDNUtUwOtshrACh";
constexpr const char *hint5 = "INTELLIGENCECHECKx7x27";

/// decrypts data encoded with the DONTBOTHER N cypher (N defaults to 17)
template<typename ST>
inline ST dontbother17_decrypt(const ST &data, unsigned long long n=17) {
	ST datacpy(data);
	ST out;
	out.reserve(datacpy.size());
	for (unsigned long long index = 0; !datacpy.empty();) {
		index = (index + n) % datacpy.size();
		out.push_back(datacpy[static_cast<size_t>(index)]);
		datacpy.erase(datacpy.begin() + static_cast<size_t>(index));
	}
	return out;
}
/// encrypts data using with the DONTBOTHER N cypher (N defaults to 17)
template<typename ST>
inline ST dontbother17_encrypt(const ST &data, unsigned long long n=17) {
	ST out(data.size(), static_cast<ST::value_type>(0u));
	std::vector<unsigned long long> free_indices(data.size(), 0);
	std::iota(free_indices.begin(), free_indices.end(), 0);
	unsigned long long index = 0;
	for (const auto &c : data) {
		index = (index + n) % free_indices.size();
		out[free_indices[static_cast<size_t>(index)]] = c;
		free_indices.erase(free_indices.begin() + static_cast<size_t>(index));
	}
	return out;
}
/// decrypts data encoded with the HCSTSBSH algorithm (key defaults to HUMANSCANTSOLVE...)
template<typename ST, typename KT>
inline ST humanscantsolvethis_decrypt(const ST &data, const KT &key=key2) {
	ST datacpy(data);
	ST out;
	out.reserve(datacpy.size());
	for (unsigned int index = 0, keyindex = 0; !datacpy.empty(); keyindex = (keyindex + 1) % key.size()) {
		index = (index + key[keyindex] - 64) % datacpy.size();
		out.push_back(datacpy[index]);
		datacpy.erase(datacpy.begin() + index);
	}
	return out;
}
/// encrypts data using the HCSTSBSH algorithm (key defaults to HUMANSCANTSOLVE...)
template<typename ST, typename KT>
inline ST humanscantsolvethis_encrypt(const ST &data, const KT &key=key2) {
	ST out(data.size(), static_cast<ST::value_type>(0));
	std::vector<unsigned int> free_indices(data.size(), 0);
	std::iota(free_indices.begin(), free_indices.end(), 0);
	unsigned int index = 0, keyindex = 0;
	for (const auto &c : data) {
		index = (index + key[keyindex] - 64) % free_indices.size();
		keyindex = (keyindex + 1) % key.size();
		out[free_indices[index]] = c;
		free_indices.erase(free_indices.begin() + index);
	}
	return out;
}
inline std::string sheismymother_decrypt(const std::string &data, const std::string &key=key3) { return humanscantsolvethis_decrypt(data, key); }
inline std::string sheismymother_encrypt(const std::string &data, const std::string &key=key3) { return humanscantsolvethis_encrypt(data, key); }
inline std::string processingpowercheck_decrypt(const std::string &data, const std::string &key=key4) { return humanscantsolvethis_decrypt(data, key); }
inline std::string processingpowercheck_encrypt(const std::string &data, const std::string &key=key4) { return humanscantsolvethis_encrypt(data, key); }

inline std::string humanscantsolvethis_decrypt_partial(const std::string &data, const std::string &key=key2, unsigned int length=100) {
	std::string datacpy(data);
	std::string out;
	out.reserve(datacpy.size());
	for (unsigned int index = 0, keyindex = 0, counter = 0; counter < length && !datacpy.empty(); keyindex = (keyindex + 1) % key.size(), counter++) {
		index = (index + key[keyindex] - 64) % datacpy.size();
		out.push_back(datacpy[index]);
		datacpy.erase(datacpy.begin() + index);
	}
	return out;
}

template<typename ST>
inline ST mask_data(const ST &data, const ST &chars) {
	ST masked(data);
	std::replace_if(masked.begin(), masked.end(), [&chars](const auto c) { return chars.find(c) == std::string::npos; }, '.');
	return masked;
}

inline std::string frequency(const std::string &data) {
	if (data.empty()) {
		return "";
	}
	std::map<char, unsigned int> freq;
	for (char c : data) { freq[c]++; }
	std::ostringstream ss;
	for (const auto &f : freq) {
		if (f.first == ' ')
			ss << " ␣-" << f.second;
		else
			ss << ' ' << f.first << '-' << f.second;
	}
	return ss.str().substr(1);
}


template<typename F>
inline void check_start(std::string &data, std::string &keybuff, unsigned int prevskip, unsigned int off, const std::string &result, F callback) {
	keybuff.push_back(static_cast<char>(prevskip + 64));
	if (keybuff.size() >= result.size()) {
		callback(keybuff);
	} else {
		char removed_char = data[off];
		data.erase(data.begin() + off);
		for (unsigned int skip = 1; skip <= 26; skip++) {
			unsigned int index = (off + skip) % data.size();
			char c = data[index];
			if (c == result[keybuff.size()])
				check_start(data, keybuff, skip, index, result, callback);
		}
		data.insert(data.begin() + off, removed_char);
	}
	keybuff.pop_back();
}
inline std::vector<std::string> humanscantsolvethis_keys_from_result(const std::string &data, const std::string &result) {
	if (data.empty()) {
		return {"empty data!"};
	} else if (result.size() > 15) {
		return {"required result is too long!"};
	}
	std::vector<std::string> res;
	std::string databuff(data);
	std::string keybuff;
	for (unsigned int skip = 1; skip <= 26; skip++) {
		unsigned int index = skip % data.size();
		char c = data[index];
		if (c == result[keybuff.size()])
			check_start(databuff, keybuff, skip, index, result, [&res](const std::string &k) { res.push_back(k); });
	}
	return res;
}

#endif
