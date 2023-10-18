package com.codenow.fellowers.model.dtio.user;

import lombok.Data;

import java.io.Serializable;
import java.util.List;

@Data
public class UserTagsRequest implements Serializable {

    List<String> tagsNameList;

    private static final long serialVersionUID = 1L;
}
