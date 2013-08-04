/* $Id$ */

/*
 * Copyright (c) 2013 Roland van Rijswijk-Deij
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*****************************************************************************
 irma_verifytests.h

 Tests credential proof verification APDU command sequence generation
 *****************************************************************************/

#include <stdlib.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <gmpxx.h>
#include "irma_verifytests.h"
#include "silvia_irma_verifier.h"
#include "silvia_verifier_spec.h"
#include "silvia_types.h"
#include "silvia_parameters.h"
#include <stdio.h>

CPPUNIT_TEST_SUITE_REGISTRATION(irma_verify_tests);

void irma_verify_tests::setUp()
{
	silvia_system_parameters::i()->set_l_n(1024);
	silvia_system_parameters::i()->set_l_m(256);
	silvia_system_parameters::i()->set_l_statzk(80);
	silvia_system_parameters::i()->set_l_H(256);
	silvia_system_parameters::i()->set_l_v(1700);
	silvia_system_parameters::i()->set_l_e(504);
	silvia_system_parameters::i()->set_l_e_prime(120);
	silvia_system_parameters::i()->set_hash_type("sha1");
}

void irma_verify_tests::tearDown()
{
	silvia_system_parameters::i()->reset();
}

void irma_verify_tests::test_verify_irma_proof_cmdgen()
{
	////////////////////////////////////////////////////////////////////
	// Issuer public key
	////////////////////////////////////////////////////////////////////
	
	mpz_class n("0x88CC7BD5EAA39006A63D1DBA18BDAF00130725597A0A46F0BACCEF163952833BCBDD4070281CC042B4255488D0E260B4D48A31D94BCA67C854737D37890C7B21184A053CD579176681093AB0EF0B8DB94AFD1812A78E1E62AE942651BB909E6F5E5A2CEF6004946CCA3F66EC21CB9AC01FF9D3E88F19AC27FC77B1903F141049");
	mpz_class Z("0x3F7BAA7B26D110054A2F427939E61AC4E844139CEEBEA24E5C6FB417FFEB8F38272FBFEEC203DB43A2A498C49B7746B809461B3D1F514308EEB31F163C5B6FD5E41FFF1EB2C5987A79496161A56E595BC9271AAA65D2F6B72F561A78DD6115F5B706D92D276B95B1C90C49981FE79C23A19A2105032F9F621848BC57352AB2AC");
	mpz_class S("0x617DB25740673217DF74BDDC8D8AC1345B54B9AEA903451EC2C6EFBE994301F9CABB254D14E4A9FD2CD3FCC2C0EFC87803F0959C9550B2D2A2EE869BCD6C5DF7B9E1E24C18E0D2809812B056CE420A75494F9C09C3405B4550FD97D57B4930F75CD9C9CE0A820733CB7E6FC1EEAF299C3844C1C9077AC705B774D7A20E77BA30");
	std::vector<mpz_class> R;
	
	R.push_back(mpz_class("0x6B4D9D7D654E4B1285D4689E12D635D4AF85167460A3B47DB9E7B80A4D476DBEEC0B8960A4ACAECF25E18477B953F028BD71C6628DD2F047D9C0A6EE8F2BC7A8B34821C14B269DBD8A95DCCD5620B60F64B132E09643CFCE900A3045331207F794D4F7B4B0513486CB04F76D62D8B14B5F031A8AD9FFF3FAB8A68E74593C5D8B"));
	R.push_back(mpz_class("0x177CB93935BB62C52557A8DD43075AA6DCDD02E2A004C56A81153595849A476C515A1FAE9E596C22BE960D3E963ECFAC68F638EBF89642798CCAE946F2F179D30ABE0EDA9A44E15E9CD24B522F6134B06AC09F72F04614D42FDBDB36B09F60F7F8B1A570789D861B7DBD40427254F0336D0923E1876527525A09CDAB261EA7EE"));
	R.push_back(mpz_class("0x12ED9D5D9C9960BACE45B7471ED93572EA0B82C611120127701E4EF22A591CDC173136A468926103736A56713FEF3111FDE19E67CE632AB140A6FF6E09245AC3D6E022CD44A7CC36BCBE6B2189960D3D47513AB2610F27D272924A84154646027B73893D3EE8554767318942A8403F0CD2A41264814388BE4DF345E479EF52A8"));
	R.push_back(mpz_class("0x7AF1083437CDAC568FF1727D9C8AC4768A15912B03A8814839CF053C85696DF3A5681558F06BAD593F8A09C4B9C3805464935E0372CBD235B18686B540963EB9310F9907077E36EED0251D2CF1D2DDD6836CF793ED23D266080BF43C31CF3D304E2055EF44D454F477354664E1025B3F134ACE59272F07D0FD4995BDAACCDC0B"));
	R.push_back(mpz_class("0x614BF5243C26D62E8C7C9B0FAE9C57F44B05714894C3DCF583D9797C423C1635F2E4F1697E92771EB98CF36999448CEFC20CB6E10931DED3927DB0DFF56E18BD3A6096F2FF1BFF1A703F3CCE6F37D589B5626354DF0DB277EF73DA8A2C7347689B79130559FB94B6260C13D8DC7D264BA26953B906488B87CDC9DFD0BC69C551"));
	R.push_back(mpz_class("0x5CAE46A432BE9DB72F3B106E2104B68F361A9B3E7B06BBE3E52E60E69832618B941C952AA2C6EEFFC222311EBBAB922F7020D609D1435A8F3F941F4373E408BE5FEBAF471D05C1B91030789F7FEA450F61D6CB9A4DD8642253327E7EBF49C1600C2A075EC9B9DEC196DDBDC373C29D1AF5CEAD34FA6993B8CDD739D04EA0D253"));
	R.push_back(mpz_class("0x52E49FE8B12BFE9F12300EF5FBDE1800D4611A587E9F4763C11E3476BBA671BFD2E868436C9E8066F96958C897DD6D291567C0C490329793F35E925B77B304249EA6B30241F5D014E1C533EAC27AA9D9FCA7049D3A8D89058969FC2CD4DC63DF38740701D5E2B7299C49EC6F190DA19F4F6BC3834EC1AE145AF51AFEBA027EAA"));
	R.push_back(mpz_class("0x05AA7EE2AD981BEE4E3D4DF8F86414797A8A38706C84C9376D324070C908724BB89B224CB5ADE8CDDB0F65EBE9965F5C710C59704C88607E3C527D57A548E24904F4991383E5028535AE21D11D5BF87C3C5178E638DDF16E666EA31F286D6D1B3251E0B1470E621BEE94CDFA1D2E47A86FD2F900D5DDCB42080DAB583CBEEEDF"));
	R.push_back(mpz_class("0x73D3AB9008DC2BD65161A0D7BFC6C29669C975B54A1339D8385BC7D5DEC88C6D4BD482BFBC7A7DE44B016646B378B6A85FBC1219D351FE475DC178F90DF4961CA980EB4F157B764EC3ECF19604FEDE0551AA42FB12B7F19667AC9F2C46D1185E66072EA709CC0D9689CE721A47D54C028D7B0B01AEEC1C4C9A03979BE9080C21"));
	R.push_back(mpz_class("0x33F10AB2D18B94D870C684B5436B38AC419C08FB065A2C608C4E2E2060FE436945A15F8D80F373B35C3230654A92F99B1A1C8D5BB10B83646A112506022AF7D4D09F7403EC5AECDB077DA945FE0BE661BAFEDDDDC5E43A4C5D1A0B28AE2AA838C6C8A7AE3DF150DBD0A207891F1D6C4001B88D1D91CF380EE15E4E632F33BD02"));
	
	silvia_pub_key pubkey(n, S, Z, R);
	
	////////////////////////////////////////////////////////////////////
	// Verifier specification
	////////////////////////////////////////////////////////////////////
	
	std::vector<std::string> attribute_names;
	std::vector<bool> D;
	
	attribute_names.push_back("expires");
	attribute_names.push_back("over12");
	attribute_names.push_back("over16");
	attribute_names.push_back("over18");
	attribute_names.push_back("over21");
	
	D.push_back(true);
	D.push_back(false);
	D.push_back(false);
	D.push_back(true);
	D.push_back(false);
	
	silvia_verifier_specification vspec("Bar", "Age: 18+", 801, 10, attribute_names, D);
	
	silvia_irma_verifier verifier(&pubkey, &vspec);
	
	std::vector<bytestring> commands = verifier.get_proof_commands();
	
	CPPUNIT_ASSERT(commands.size() == 12);
	CPPUNIT_ASSERT(commands[0] == "00A404000849524D416361726400");
	CPPUNIT_ASSERT(commands[1].substr(0, 7) == "8020000028000A");
	CPPUNIT_ASSERT(commands[1].substr(39, 2) == "0012");
	CPPUNIT_ASSERT(commands[2].substr(0, 5) == "802A00000A");
	CPPUNIT_ASSERT(commands[3] == "802B0100");
	CPPUNIT_ASSERT(commands[4] == "802B0200");
	CPPUNIT_ASSERT(commands[5] == "802B0300");
	CPPUNIT_ASSERT(commands[6] == "802C0000");
	CPPUNIT_ASSERT(commands[7] == "802C0100");
	CPPUNIT_ASSERT(commands[8] == "802C0200");
	CPPUNIT_ASSERT(commands[9] == "802C0300");
	CPPUNIT_ASSERT(commands[10] == "802C0400");
	CPPUNIT_ASSERT(commands[11] == "802C0500");
}

