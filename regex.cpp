#include <regex>
#include "regex.h"
#include "json.h"

Regex::Regex () : Extender ( L"Regex" ) {
	methods.AddFunction ( L"Select", L"Выбрать", 2, [ & ] ( tVariant* Params, tVariant* Result ) {
		return select ( Params, Result );
	} );
	methods.AddFunction ( L"Test", L"Тест", 2, [ & ] ( tVariant* Params, tVariant* Result ) {
		return test ( Params, Result );
	} );
	methods.AddFunction ( L"Replace", L"Заменить", 3, [ & ] ( tVariant* Params, tVariant* Result ) {
		return replace ( Params, Result );
	} );
}

bool Regex::select ( tVariant* Params, tVariant* Result ) {
	std::wstring string { Chars::WCHARToWide ( Params->pwstrVal, Params->wstrLen ) };
	auto next = Params + 1;
	std::wstring query = Chars::WCHARToWide ( next->pwstrVal, next->wstrLen );
	std::wsmatch match;
	try {
		std::regex_search ( string, match, Init ( query ) );
	} catch ( const std::exception& e ) {
		SetError ( e.what () );
		return false;
	} catch ( ... ) {
		SetError ( "Unknown error occurred in std::regex_search" );
		return false;
	}
	using namespace JSON;
	Array json;
	for ( size_t i = 0; i < match.size (); ++i ) {
		json.Add<String> ()->Set ( match.str ( i ) );
	}
	std::wstring result;
	json.Presentation ( &result );
	returnString ( Result, result );
	return true;
}

std::wregex Regex::Init ( const std::wstring& Pattern ) {
	std::wregex object;
	object.imbue ( std::locale ( "ru_RU.UTF-8" ) );
	object.assign ( Pattern, std::regex_constants::icase );
	return object;
}

bool Regex::test ( tVariant* Params, tVariant* Result ) {
	std::wstring string { Chars::WCHARToWide ( Params->pwstrVal, Params->wstrLen ) };
	auto next = Params + 1;
	std::wstring query = Chars::WCHARToWide ( next->pwstrVal, next->wstrLen );
	std::wsmatch match;
	try {
		returnBool ( Result, std::regex_search ( string, match, Init ( query ) ) );
	} catch ( const std::exception& e ) {
		SetError ( e.what () );
		return false;
	} catch ( ... ) {
		SetError ( "Unknown error occurred in std::regex_search" );
		return false;
	}
	return true;
}

bool Regex::replace ( tVariant* Params, tVariant* Result ) {
	std::wstring string { Chars::WCHARToWide ( Params->pwstrVal, Params->wstrLen ) };
	auto next = Params + 1;
	std::wstring query = Chars::WCHARToWide ( next->pwstrVal, next->wstrLen );
	++next;
	std::wstring replacement = Chars::WCHARToWide ( next->pwstrVal, next->wstrLen );
	std::wsmatch match;
	try {
		returnString ( Result, std::regex_replace ( string, Init ( query ), replacement ) );
	} catch ( const std::exception& e ) {
		SetError ( e.what () );
		return false;
	} catch ( ... ) {
		SetError ( "Unknown error occurred in std::regex_replace" );
		return false;
	}
	return true;
}