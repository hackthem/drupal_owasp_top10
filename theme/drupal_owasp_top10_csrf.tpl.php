<style>
mark { 
    background-color: red;
    color: white;
}
</style>


<div class="container-fluid">

	<div class="col-md-6 col-md-offset-3">

		<div class="panel panel-info">
			<div class="panel-heading">
				<h3 class="panel-title">Information</h3>
			</div>
			<div class="panel-body">
				Here we have a table containing a list of users accessible to admin.
				<br>
				The admin can delete any user he wants. The aim of this demonstration is to show how an attacker 
				can force the admin to delete a specific user.
				<br>
				The attacker will inviter the admin to visit this site :<br>
				<a href="http://hackthem.free.fr/csrf_safe.php">http://hackthem.free.fr/csrf_safe.php</a>
				<br>
				The malicious code is bellow :
				<pre class="language-markup"><code><?php echo "malicous code variable" ;?></code></pre>
				Here the attack will occur because an anti-csrf token is not implemented.
			</div>
		</div>

		<div class="panel panel-default">
			<div class="panel-heading"> 
				<a class="accordion-toggle collapsed" data-toggle="collapse" href="#collapseOne"> HTML Code </a>
			</div>
			<div id="collapseOne" class="panel-collapse collapse">
				<div class="panel-body">
    				<pre class="language-markup"><code><?php echo "html code variable" ; ?></code></pre>
				</div>  					
			</div>
	    </div>

	</div>

	<div class="col-md-6 col-md-offset-3">
		<div class="panel panel-info">
			<div class="panel-heading"> 
				List of users
			</div>
			<div class="panel-body">
				<table class="table table-striped">

					<thead>
						<tr>
							<th>USERNAME</th>
							<th>FIRST NAME</th>
							<th>LAST NAME</th>
							<th>ADDRESS</th>
						</tr>
					</thead>
					<tbody>
						<?php foreach ($users as $user): ?>
						<tr>
							<td>
								<?php echo $user->username ; ?>
							</td>
							<td>
								<?php echo $user->first_name ;?>
							</td>
							<td>
								<?php echo $user->last_name ;?>
							</td>
							<td>
								<?php echo $user['address'] ?>
							</td>
							<td>
								<FORM method="POST" action="/demo_csrf.php?csrf=safe">
									<INPUT type="hidden" name="demo_csrf_safe_action" value="delete"> 
									<INPUT type="hidden" name="user_id" value="<?php echo $user->user_id ;?>"> 
									 
									<INPUT type="submit" value="delete" >
								</FORM>
							</td>
						</tr>
						<?php endforeach ?>
					</tbody>
				</table>
			</div>
		</div>
	</div>

	<div class="col-md-6 col-md-offset-3">

		<div class="panel panel-success">
			<div class="panel-heading">
				PHP Code with ANTI CSRF TOKEN
			</div>
			<div class="panel-body">		
    			<pre class="language-php"><code><?php echo "php_code"; ?></code></pre>
    		</div>
	    </div>        

	</div>

	 
</div>


