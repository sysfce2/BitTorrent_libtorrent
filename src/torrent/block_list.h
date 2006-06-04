// libTorrent - BitTorrent library
// Copyright (C) 2005-2006, Jari Sundell
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// In addition, as a special exception, the copyright holders give
// permission to link the code of portions of this program with the
// OpenSSL library under certain conditions as described in each
// individual source file, and distribute linked combinations
// including the two.
//
// You must obey the GNU General Public License in all respects for
// all of the code used other than OpenSSL.  If you modify file(s)
// with this exception, you may extend this exception to your version
// of the file(s), but you are not obligated to do so.  If you do not
// wish to do so, delete this exception statement from your version.
// If you delete this exception statement from all source files in the
// program, then also delete it here.
//
// Contact:  Jari Sundell <jaris@ifi.uio.no>
//
//           Skomakerveien 33
//           3185 Skoppum, NORWAY

#ifndef LIBTORRENT_BLOCK_LIST_H
#define LIBTORRENT_BLOCK_LIST_H

#include <vector>
#include <inttypes.h>
#include <torrent/block.h>
#include <torrent/piece.h>

namespace torrent {

class BlockList : public std::vector<Block> {
public:
  typedef std::vector<Block> base_type;
  typedef uint32_t           size_type;

  // Consolidate the different priority types into one.
  typedef enum {
    STOPPED,
    NORMAL,
    HIGH
  } priority_type;

  using base_type::value_type;
  using base_type::reference;
  using base_type::difference_type;

  using base_type::iterator;
  using base_type::reverse_iterator;
  using base_type::size;
  using base_type::empty;

  using base_type::begin;
  using base_type::end;
  using base_type::rbegin;
  using base_type::rend;

  using base_type::operator[];

  BlockList() {}
  BlockList(const Piece& piece, uint32_t blockLength);
  ~BlockList();

  const Piece&        piece() const                 { return m_piece; }

  uint32_t            index() const                 { return m_piece.index(); }

  // Set when the chunk was initially requested from a seeder. This
  // allows us to quickly determine if it is a suitable chunk to
  // request from another seeder, e.g by already knowing it is a rare
  // piece.
  bool                by_seeder() const             { return m_bySeeder; }
  void                set_by_seeder(bool state)     { m_bySeeder = state; }

  priority_type       priority() const              { return m_priority; }
  void                set_priority(priority_type p) { m_priority = p; }

  // Temp hack.
  int32_t             priority_int() const          { return static_cast<int32_t>(m_priority); }

private:
  Piece               m_piece;
  priority_type       m_priority;

  bool                m_bySeeder;
};

}

#endif