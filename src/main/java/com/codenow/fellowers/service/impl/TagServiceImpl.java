package com.codenow.fellowers.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.codenow.fellowers.model.entity.Tag;
import com.codenow.fellowers.service.TagService;
import com.codenow.fellowers.mapper.TagMapper;
import org.springframework.stereotype.Service;

/**
 * @author axliu
 */
@Service
public class TagServiceImpl extends ServiceImpl<TagMapper, Tag>
        implements TagService {
}





