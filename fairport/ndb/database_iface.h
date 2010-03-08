#ifndef FAIRPORT_NDB_DATABASE_IFACE_H
#define FAIRPORT_NDB_DATABASE_IFACE_H

#include <memory>

#include "fairport/util/util.h"
#include "fairport/util/primatives.h"

namespace fairport
{

class node;

struct block_info
{
    block_id id;
    ulonglong address;
    ushort size;
    ushort ref_count;
};

struct node_info
{
    node_id id;
    block_id data_bid;
    block_id sub_bid;
    node_id parent_id;
};

struct subnode_info
{
    node_id id;
    block_id data_bid;
    block_id sub_bid;
};

template<typename K, typename V>
class bt_page;
typedef bt_page<node_id, node_info> nbt_page;
typedef bt_page<block_id, block_info> bbt_page;

template<typename K, typename V>
class bt_nonleaf_page;
typedef bt_nonleaf_page<node_id, node_info> nbt_nonleaf_page;
typedef bt_nonleaf_page<block_id, block_info> bbt_nonleaf_page;

template<typename K, typename V>
class bt_leaf_page;
typedef bt_leaf_page<node_id, node_info> nbt_leaf_page;
typedef bt_leaf_page<block_id, block_info> bbt_leaf_page;

template<typename K, typename V>
class const_btree_node_iter;

typedef const_btree_node_iter<node_id, node_info> const_nodeinfo_iterator;
typedef const_btree_node_iter<node_id, subnode_info> const_subnodeinfo_iterator;
typedef const_btree_node_iter<block_id, block_info> const_blockinfo_iterator;

class block;
class data_block;
class extended_block;
class external_block;
class subnode_block;
class subnode_leaf_block;
class subnode_nonleaf_block;

class db_context;
typedef std::shared_ptr<db_context> shared_db_ptr;
typedef std::weak_ptr<db_context> weak_db_ptr;

// database external interface
class db_context : public std::enable_shared_from_this<db_context>
{
public:
    virtual ~db_context() { }

    virtual node lookup_node(node_id nid) = 0;
    virtual node_info lookup_node_info(node_id nid) = 0;
    virtual block_info lookup_block_info(block_id bid) = 0;
   
    // page factory functions
	virtual std::shared_ptr<bbt_page> read_bbt_root() = 0;
	virtual std::shared_ptr<nbt_page> read_nbt_root() = 0;
	virtual std::shared_ptr<bbt_page> read_bbt_page(ulonglong location) = 0;
	virtual std::shared_ptr<nbt_page> read_nbt_page(ulonglong location) = 0;
	virtual std::shared_ptr<nbt_leaf_page> read_nbt_leaf_page(ulonglong location) = 0;
	virtual std::shared_ptr<bbt_leaf_page> read_bbt_leaf_page(ulonglong location) = 0;
	virtual std::shared_ptr<nbt_nonleaf_page> read_nbt_nonleaf_page(ulonglong location) = 0;
    virtual std::shared_ptr<bbt_nonleaf_page> read_bbt_nonleaf_page(ulonglong location) = 0;

    // block factory functions
	std::shared_ptr<block> read_block(block_id bid) { return read_block(shared_from_this(), bid); }
	std::shared_ptr<data_block> read_data_block(block_id bid) { return read_data_block(shared_from_this(), bid); }
	std::shared_ptr<extended_block> read_extended_block(block_id bid) { return read_extended_block(shared_from_this(), bid); }
	std::shared_ptr<external_block> read_external_block(block_id bid) { return read_external_block(shared_from_this(), bid); }
	std::shared_ptr<subnode_block> read_subnode_block(block_id bid) { return read_subnode_block(shared_from_this(), bid); }
	std::shared_ptr<subnode_leaf_block> read_subnode_leaf_block(block_id bid) { return read_subnode_leaf_block(shared_from_this(), bid); }
	std::shared_ptr<subnode_nonleaf_block> read_subnode_nonleaf_block(block_id bid) { return read_subnode_nonleaf_block(shared_from_this(), bid); }
    virtual std::shared_ptr<block> read_block(const shared_db_ptr& parent, block_id bid) = 0;
    virtual std::shared_ptr<data_block> read_data_block(const shared_db_ptr& parent, block_id bid) = 0;
    virtual std::shared_ptr<extended_block> read_extended_block(const shared_db_ptr& parent, block_id bid) = 0;
    virtual std::shared_ptr<external_block> read_external_block(const shared_db_ptr& parent, block_id bid) = 0;
    virtual std::shared_ptr<subnode_block> read_subnode_block(const shared_db_ptr& parent, block_id bid) = 0;
    virtual std::shared_ptr<subnode_leaf_block> read_subnode_leaf_block(const shared_db_ptr& parent, block_id bid) = 0;
    virtual std::shared_ptr<subnode_nonleaf_block> read_subnode_nonleaf_block(const shared_db_ptr& parent, block_id bid) = 0;

	std::shared_ptr<block> read_block(const block_info& bi) { return read_block(shared_from_this(), bi); }
	std::shared_ptr<data_block> read_data_block(const block_info& bi) { return read_data_block(shared_from_this(), bi); }
	std::shared_ptr<extended_block> read_extended_block(const block_info& bi) { return read_extended_block(shared_from_this(), bi); }
	std::shared_ptr<external_block> read_external_block(const block_info& bi) { return read_external_block(shared_from_this(), bi); }
	std::shared_ptr<subnode_block> read_subnode_block(const block_info& bi) { return read_subnode_block(shared_from_this(), bi); }
	std::shared_ptr<subnode_leaf_block> read_subnode_leaf_block(const block_info& bi) { return read_subnode_leaf_block(shared_from_this(), bi); }
	std::shared_ptr<subnode_nonleaf_block> read_subnode_nonleaf_block(const block_info& bi) { return read_subnode_nonleaf_block(shared_from_this(), bi); }
    virtual std::shared_ptr<block> read_block(const shared_db_ptr& parent, const block_info& bi) = 0;
    virtual std::shared_ptr<data_block> read_data_block(const shared_db_ptr& parent, const block_info& bi) = 0;
    virtual std::shared_ptr<extended_block> read_extended_block(const shared_db_ptr& parent, const block_info& bi) = 0;
    virtual std::shared_ptr<external_block> read_external_block(const shared_db_ptr& parent, const block_info& bi) = 0;
    virtual std::shared_ptr<subnode_block> read_subnode_block(const shared_db_ptr& parent, const block_info& bi) = 0;
    virtual std::shared_ptr<subnode_leaf_block> read_subnode_leaf_block(const shared_db_ptr& parent, const block_info& bi) = 0;
    virtual std::shared_ptr<subnode_nonleaf_block> read_subnode_nonleaf_block(const shared_db_ptr& parent, const block_info& bi) = 0;

	std::shared_ptr<external_block> create_external_block(size_t size) { return create_external_block(shared_from_this(), size); }
	std::shared_ptr<extended_block> create_extended_block(std::shared_ptr<external_block>& pblock) { return create_extended_block(shared_from_this(), pblock); }
	std::shared_ptr<extended_block> create_extended_block(std::shared_ptr<extended_block>& pblock) { return create_extended_block(shared_from_this(), pblock); }
	std::shared_ptr<extended_block> create_extended_block(size_t size) { return create_extended_block(shared_from_this(), size); }
    virtual std::shared_ptr<external_block> create_external_block(const shared_db_ptr& parent, size_t size) = 0;
    virtual std::shared_ptr<extended_block> create_extended_block(const shared_db_ptr& parent, std::shared_ptr<external_block>& pblock) = 0;
    virtual std::shared_ptr<extended_block> create_extended_block(const shared_db_ptr& parent, std::shared_ptr<extended_block>& pblock) = 0;
    virtual std::shared_ptr<extended_block> create_extended_block(const shared_db_ptr& parent, size_t size) = 0;

    // header functions
    virtual block_id alloc_bid(bool is_internal) = 0;

    // context support
    //virtual shared_db_ptr create_context() = 0;
    //virtual void save(const shared_db_ptr& ctx) = 0;
};

}

#endif

