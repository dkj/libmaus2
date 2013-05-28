/*
    libmaus
    Copyright (C) 2009-2013 German Tischler
    Copyright (C) 2011-2013 Genome Research Limited

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#if ! defined(LIBMAUS_BAMBAM_BAMFLAGBASE)
#define LIBMAUS_BAMBAM_BAMFLAGBASE

#include <ostream>
#include <deque>
#include <libmaus/exception/LibMausException.hpp>
#include <libmaus/util/stringFunctions.hpp>

namespace libmaus
{
	namespace bambam
	{
		struct BamFlagBase
		{
			enum bam_flags
			{
				LIBMAUS_BAMBAM_FPAIRED = (1u << 0),
				LIBMAUS_BAMBAM_FPROPER_PAIR = (1u << 1),
				LIBMAUS_BAMBAM_FUNMAP = (1u << 2),
				LIBMAUS_BAMBAM_FMUNMAP = (1u << 3),
				LIBMAUS_BAMBAM_FREVERSE = (1u << 4),
				LIBMAUS_BAMBAM_FMREVERSE = (1u << 5),
				LIBMAUS_BAMBAM_FREAD1 = (1u << 6),
				LIBMAUS_BAMBAM_FREAD2 = (1u << 7),
				LIBMAUS_BAMBAM_FSECONDARY = (1u << 8),
				LIBMAUS_BAMBAM_FQCFAIL = (1u << 9),
				LIBMAUS_BAMBAM_FDUP = (1u << 10)
			};
			
			enum bam_cigar_ops
			{
				LIBMAUS_BAMBAM_CMATCH = 0,
				LIBMAUS_BAMBAM_CINS = 1,
				LIBMAUS_BAMBAM_CDEL = 2,
				LIBMAUS_BAMBAM_CREF_SKIP = 3,
				LIBMAUS_BAMBAM_CSOFT_CLIP = 4,
				LIBMAUS_BAMBAM_CHARD_CLIP = 5,
				LIBMAUS_BAMBAM_CPAD = 6,
				LIBMAUS_BAMBAM_CEQUAL = 7,
				LIBMAUS_BAMBAM_CDIFF = 8
			};			

			static uint64_t stringToFlag(std::string const & s)
			{
				if ( s == "PAIRED" )
					return ::libmaus::bambam::BamFlagBase::LIBMAUS_BAMBAM_FPAIRED;
				else if ( s == "PROPER_PAIR" )
					return ::libmaus::bambam::BamFlagBase::LIBMAUS_BAMBAM_FPROPER_PAIR;
				else if ( s == "UNMAP" )
					return ::libmaus::bambam::BamFlagBase::LIBMAUS_BAMBAM_FUNMAP;
				else if ( s == "MUNMAP" )
					return ::libmaus::bambam::BamFlagBase::LIBMAUS_BAMBAM_FMUNMAP;
				else if ( s == "REVERSE" )
					return ::libmaus::bambam::BamFlagBase::LIBMAUS_BAMBAM_FREVERSE;
				else if ( s == "MREVERSE" )
					return ::libmaus::bambam::BamFlagBase::LIBMAUS_BAMBAM_FMREVERSE;
				else if ( s == "READ1" )
					return ::libmaus::bambam::BamFlagBase::LIBMAUS_BAMBAM_FREAD1;
				else if ( s == "READ2" )
					return ::libmaus::bambam::BamFlagBase::LIBMAUS_BAMBAM_FREAD2;
				else if ( s == "SECONDARY" )
					return ::libmaus::bambam::BamFlagBase::LIBMAUS_BAMBAM_FSECONDARY;
				else if ( s == "QCFAIL" )
					return ::libmaus::bambam::BamFlagBase::LIBMAUS_BAMBAM_FQCFAIL;
				else if ( s == "DUP" )
					return ::libmaus::bambam::BamFlagBase::LIBMAUS_BAMBAM_FDUP;
				else
				{
					::libmaus::exception::LibMausException se;
					se.getStream() << "Unknown flag " << s << std::endl;
					se.finish();
					throw se;
				}
			}

			static uint64_t stringToFlags(std::string const & s)
			{
				std::deque<std::string> const tokens = ::libmaus::util::stringFunctions::tokenize(s,std::string(","));
				uint64_t flags = 0;
				
				for ( uint64_t i = 0; i < tokens.size(); ++i )
					flags |= stringToFlag(tokens[i]);
					
				return flags;
			}
		};
		
		inline std::ostream & operator<<(std::ostream & out, BamFlagBase::bam_flags const f)
		{
			switch ( f )
			{
				case BamFlagBase::LIBMAUS_BAMBAM_FPAIRED: out << "LIBMAUS_BAMBAM_FPAIRED"; break;
				case BamFlagBase::LIBMAUS_BAMBAM_FPROPER_PAIR: out << "LIBMAUS_BAMBAM_FPROPER_PAIR"; break;
				case BamFlagBase::LIBMAUS_BAMBAM_FUNMAP: out << "LIBMAUS_BAMBAM_FUNMAP"; break;
				case BamFlagBase::LIBMAUS_BAMBAM_FMUNMAP: out << "LIBMAUS_BAMBAM_FMUNMAP"; break;
				case BamFlagBase::LIBMAUS_BAMBAM_FREVERSE: out << "LIBMAUS_BAMBAM_FREVERSE"; break;
				case BamFlagBase::LIBMAUS_BAMBAM_FMREVERSE: out << "LIBMAUS_BAMBAM_FMREVERSE"; break;
				case BamFlagBase::LIBMAUS_BAMBAM_FREAD1: out << "LIBMAUS_BAMBAM_FREAD1"; break;
				case BamFlagBase::LIBMAUS_BAMBAM_FREAD2: out << "LIBMAUS_BAMBAM_FREAD2"; break;
				case BamFlagBase::LIBMAUS_BAMBAM_FSECONDARY: out << "LIBMAUS_BAMBAM_FSECONDARY"; break;
				case BamFlagBase::LIBMAUS_BAMBAM_FQCFAIL: out << "LIBMAUS_BAMBAM_FQCFAIL"; break;
				case BamFlagBase::LIBMAUS_BAMBAM_FDUP: out << "LIBMAUS_BAMBAM_FDUP"; break;
			}
			
			return out;
		}
	}
}
#endif
