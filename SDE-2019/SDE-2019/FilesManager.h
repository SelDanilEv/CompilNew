#pragma once

namespace FilesManager 
{
	void WriteFiles(LexA::Tables tables,Log::LOG&);
	void WriteFiles(LexA::Tables tables, std::ofstream&);
	void WriteFiles(LexA::Tables tables);
}
