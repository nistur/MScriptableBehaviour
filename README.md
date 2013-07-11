MScriptableBehavior
===================

An attempt to be able to define Maratis behaviors in lua scripts.

Usage
-----

Any scripts placed in a folder `behaviors/` within the project root will get picked up by the plugin. They require as a minimum, a table with the same name as the script. For example, within `behaviors/testbehavior.lua`:
```testbehavior = {
    onBegin = function(obj, bh)
    end,
    update = function(obj, bh)
    end,
    onEnd = function(obj, bh)
    end,
}```

_Note:_ testbehavior is not a behavior instance, any data associated with it is global so it is not possible to assign instance variables to it within any of the callbacks. It is therefore required to provide an instance store manually. For example:

```testbehavior_vars = {}
testbehavior = {
    onBegin = function(obj, bh)
        testbehavior_vars[obj] = {}
        testbehavior_vars[obj].speed = 3
    end,

    update = function(obj, bh)
        -- do something with testbehavior_vars[obj].speed
    end,
}```

### Optional plugins

If ```MScriptableBehavior``` is added to a project with ```MEvent``` and ```MScriptExt``` plugins then an extended API will be provided. With it you can specify a behavior object which can contain instance data. For example:

```MScriptableBehavior "testbehavior" {
    speed = 3,

    onBegin = function(self)
    end,

    update = function(self)
        -- do something with self.speed
    end,
}```

_Note:_ None of the standard Maratis API (such as activate(obj)) so for the time being, they will have to be manually used as follows:

```update = function(self)
    -- this makes no sense, but it's an example
    activate(self.__id.object) 
end```

### TODO

Wrap up the standard Maratis API functions so `self.__id` is no longer needed

Expose variables to the Maratis editor. The problem with this is that currently the script state is not valid within the editor. It will mean having to load the script when the plugin is loaded, check the table for exposed values, load them into the behaviour definitions and then when the first game update is run, push the values back, at which point the values should be linked, in case someone uses the variables to modify the behaviors at runtime.

Normalise everything to behavior rather than behaviour