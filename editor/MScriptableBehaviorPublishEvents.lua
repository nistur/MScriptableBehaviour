if isEditor() and editor then

local dirname = "behaviors/"

editor.publish_event {
	publish = function()
		local pkg = openPackage(getProjectName() .. ".npk")
		local files = readDirectory(dirname);
		for i=1, #files do
			packageAddFile(pkg, dirname .. files[i])
		end
		closePackage(pkg)
	end
}

end