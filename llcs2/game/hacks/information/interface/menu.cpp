#include <game/game.hpp>

void hacks::Menu::onPresent( ) {
	if ( !_state )
		return;

	if ( ImGui::Begin( "LLCS2 Menu" ) ) {
		ImGui::Checkbox( "ESP", _runtime->getConfig( )->getValueForWrite< bool >( _( "esp.enabled" ) ) );

		ImGui::Separator( );

		ImGui::Checkbox( "Shading", _runtime->getConfig( )->getValueForWrite< bool >( _( "shading.enabled" ) ) );

		ImGui::Checkbox( "Color correction", _runtime->getConfig( )->getValueForWrite< bool >( _( "shading.cc.enabled" ) ) );

		ImGui::SliderFloat( "Exposure Min", _runtime->getConfig( )->getValueForWrite< float >( _( "shading.cc.expmin" ) ), .1f, 4.f );
		ImGui::SliderFloat( "Exposure Max", _runtime->getConfig( )->getValueForWrite< float >( _( "shading.cc.expmax" ) ), .1f, 4.f );

		ImGui::Checkbox( "Fog", _runtime->getConfig( )->getValueForWrite< bool >( _( "shading.fog.enabled" ) ) );

		ImGui::SliderFloat( "Fog Start", _runtime->getConfig( )->getValueForWrite< float >( _( "shading.fog.start" ) ), 0.f, 1000.f );
		ImGui::SliderFloat( "Fog End", _runtime->getConfig( )->getValueForWrite< float >( _( "shading.fog.end" ) ), 0.f, 1000.f );
		ImGui::SliderFloat( "Fog Exposure", _runtime->getConfig( )->getValueForWrite< float >( _( "shading.fog.exposure" ) ), 0.f, 10.f );
		ImGui::SliderFloat( "Fog Density", _runtime->getConfig( )->getValueForWrite< float >( _( "shading.fog.maxdensity" ) ), 0.f, 1000.f );

		ImGui::ColorEdit4( "Fog Primary Color", _runtime->getConfig( )->getValueForWrite< float >( _( "shading.fog.primcolor" ) ) );
		ImGui::ColorEdit4( "Fog Secondary Color", _runtime->getConfig( )->getValueForWrite< float >( _( "shading.fog.seccolor" ) ) );

		ImGui::End( );
	}
}