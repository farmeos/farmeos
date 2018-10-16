# farmeos


uint32_t farmeos::random(account_name name, uint64_t game_id)
{

    asset pool_eos = token(EOS_CON).get_balance(_self, EOS_SYMBOL);
    auto mixd = tapos_block_prefix()*tapos_block_num() + name + game_id - current_time() + pool_eos.amount;
//    print("  mixd", mixd);

    const char *mixedChar = reinterpret_cast<const char *>(&mixd);

    checksum256 result;
    sha256((char *)mixedChar, sizeof(mixedChar), &result);

    uint64_t random_num = *(uint64_t*)(&result.hash[0]) + *(uint64_t*)(&result.hash[8]) + *(uint64_t*)(&result.hash[16]) +  *(uint64_t*)(&result.hash[24]);
//    print(" random:", random_num);

    return (uint32_t)(random_num%100 + 1);
}

