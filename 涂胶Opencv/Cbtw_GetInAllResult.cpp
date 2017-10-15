#include "stdafx.h"
#include "Cbtw_GetInAllResult.h"

Cbtw_GetInAllResult::Cbtw_GetInAllResult()
{
}
void Cbtw_GetInAllResult::writeOneLeagth(vector<float> Leagth)
{
	OneLeagth = Leagth;
}
void Cbtw_GetInAllResult::writeOneResult(string Result)
{
	OneResult = Result;
}
vector<float> Cbtw_GetInAllResult:: getOneLeagth()
{
	return OneLeagth;
}
string Cbtw_GetInAllResult::getOneResult()
{
	return OneResult;
}
Cbtw_GetInAllResult::~Cbtw_GetInAllResult()
{

}
